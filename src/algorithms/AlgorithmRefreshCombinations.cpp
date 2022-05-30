#include "AlgorithmRefreshCombinations.hpp"

#include <iostream>
using namespace std;

AlgorithmRefreshCombinations::AlgorithmRefreshCombinations(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_, data_)
{
    //cout << "AlgorithmRefreshCombinations::AlgorithmRefreshCombinations()" << endl;
    field_states = std::vector<FieldCombinationState>(grid.S, FCS_UNASSIGNED);
    choice_stack = std::vector<unsigned int>();
    segment_of_choice_stack = std::vector<unsigned int>();
    modifications_stack = std::vector<unsigned int>();
    current_segment_mine_count = 0;
    remaining_mines = 0;
    remaining_fields = 0;

    mine_counts_in_segment = std::vector<std::vector<unsigned int>>(grid.M, std::vector<unsigned int>());
    current_mine_count_id_in_segment = std::vector<size_t>(grid.M, 0);

    segments_combinations = std::vector<std::map<unsigned int, long double>>(grid.M, std::map<unsigned int, long double>());
    field_combinations_temp = std::vector<std::map<unsigned int, long double>>(grid.S, std::map<unsigned int, long double>());
}

AlgorithmRefreshCombinations::~AlgorithmRefreshCombinations() {}

bool AlgorithmRefreshCombinations::Run()
{
    cout << "AlgorithmRefreshCombinations::Run() =================================================================" << endl;
    Clear();
    remaining_mines = grid.M - grid.flags_index;
    remaining_fields = grid.S - grid.visible_fields_index - grid.flags_index - data.face_index;
    const unsigned int segments_to_check = data.segments_count;
    for(size_t i = 0; i < segments_to_check; i++)
    {
        GetCombinationsForSegment(i);
    }
    MergeAllSegmentsCombinations();

    return true;
}

// only called once at the beginning of Run
void AlgorithmRefreshCombinations::Clear()
{
    //cout << "AlgorithmRefreshCombinations::Clear()" << endl;
    // Only clearing fields that are going to be used
    const unsigned int sections_to_clear = data.segments_index;
    for(size_t i = 0; i < sections_to_clear; i++)
    {
        const unsigned int current_section = data.segments[i];
        const unsigned int section_begin = current_section * MAX_SECTION_LENGTH;
        const unsigned int section_end = section_begin + data.sections_l[current_section];
        for(size_t j = section_begin; j < section_end; j++)
        {
            const unsigned int section_field = data.sections[j];
            field_states[section_field] = FCS_UNASSIGNED;
            data.field_combinations[section_field].clear();
            field_combinations_temp[section_field].clear();
        }
    }
    const unsigned int segments_count = data.segments_count;
    for(size_t i = 0; i < segments_count; i++)
    {
        segments_combinations[i].clear();
        mine_counts_in_segment[i].clear();
        current_mine_count_id_in_segment[i] = 0;
    }
    data.remaining_fields_mine_count_combinations.clear();
    data.total_combinations = 0.0L;
}

void AlgorithmRefreshCombinations::GetCombinationsForSegment(unsigned int segment_id)
{
    cout << "AlgorithmRefreshCombinations::GetCombinationsForSegment(" << segment_id << ")" << endl;
    std::vector<SubsegmentData>& subsegments_ref = data.subsegments[segment_id];
    do
    {
        const long double combination_multiplier = ApplySubsegmentsCombination(subsegments_ref);
        GetCombinationsForFixedSubsegments(segment_id, combination_multiplier);
    } while (NextSubsegmentsCombination(subsegments_ref));
}

long double AlgorithmRefreshCombinations::ApplySubsegmentsCombination(std::vector<SubsegmentData>& subsegments_ref)
{
    cout << "AlgorithmRefreshCombinations::ApplySubsegmentsCombination()" << endl;
    // returns the weight of the combination. it is the multiplier of the number of mine combinations
    // of the entire segment for this particular set of subsegments values combination
    current_segment_mine_count = 0;
    long double subsegment_combination_weight = 1.0L;
    const size_t subsegments_max = subsegments_ref.size();
    for(size_t subsegment_id = 0; subsegment_id < subsegments_max; subsegment_id++)
    {
        SubsegmentData& subsegment = subsegments_ref[subsegment_id];
        const unsigned char mines_to_add = subsegment.possible_values[subsegment.current_possibility_id];
        subsegment_combination_weight = subsegment_combination_weight * subsegment.combinations_for_value[mines_to_add];
        const size_t subsegment_l = subsegment.fields.size();
        for(size_t i = 0; i < subsegment_l; i++)
        {
            const unsigned int subsegment_field = subsegment.fields[i];
            if(i < mines_to_add) { field_states[subsegment_field] = FCS_MINE; current_segment_mine_count++; }
            else                 { field_states[subsegment_field] = FCS_SAFE; }
        }
    }
    return subsegment_combination_weight;
}

void AlgorithmRefreshCombinations::GetCombinationsForFixedSubsegments(const unsigned int segment_id, const long double combination_multiplier)
{
    //cout << "AlgorithmRefreshCombinations::GetCombinationsForFixedSubsegments()" << endl;
    choice_stack.clear();
    modifications_stack.clear();
    modifications_stack.clear();
    const unsigned int segment_begin = data.segments_starting_indexes[segment_id];
    const unsigned int segment_end = segment_begin + data.segments_l[segment_id];
    size_t segment_head = segment_begin;
    // dirty loop. segment_head may be going back and forth but will always terminate
    while(true)
    {
        const unsigned int section_origin = data.segments[segment_head];
        const unsigned char section_l = data.sections_l[section_origin];
        const unsigned int section_begin = section_origin * MAX_SECTION_LENGTH;
        const unsigned int section_end = section_begin + section_l;
        char remaining_section_value = data.sections_values[section_origin];
        char remaining_section_length = 0;
        GetRemainingSectionValue(section_begin, section_end, remaining_section_value, remaining_section_length);
        // check if previous choices have already made this section contain a contradiction
        if(remaining_section_value < 0) 
        {
            cout << "contadiction generated previously. remaining_section_value == " << int(remaining_section_value) << endl;
            bool revert_success = RevertSegmentHeadToLastChoice(segment_head);
            if(revert_success) { continue; }
            else               { break; }
        }

        // Apply state transitions
        for(size_t section_head = section_begin; section_head < section_end; section_head++)
        {
            const unsigned int section_field = data.sections[section_head];
            TransitionFieldStateForward(section_field, segment_head, remaining_section_value, remaining_section_length);
        }

        // check if enough mines were put into the section
        if(remaining_section_value != 0)
        {
            cout << "contradiction generated now. remaining_section_value == " << int(remaining_section_value) << endl;
            bool revert_success = RevertSegmentHeadToLastChoice(segment_head);
            if(revert_success) { continue; }
            else               { break; }
        }

        segment_head++;

        // if no contradictions were found until the last segment, this combination is valid
        if(segment_head == segment_end)
        {
            cout << "valid combination" << endl;
            ApplyCurrentCombinationAsValid(segment_id, combination_multiplier);
            bool revert_success = RevertSegmentHeadToLastChoice(segment_head);
            if(revert_success) { continue; }
            else               { break; }
        }
    }
}

void AlgorithmRefreshCombinations::GetRemainingSectionValue(const unsigned int section_begin, const unsigned int section_end, char& section_value, char& section_length)
{
    //cout << "AlgorithmRefreshCombinations::GetRemainingSectionValue()" << endl;
    std::vector<unsigned int>& sections = data.sections;
    for(size_t section_head = section_begin; section_head < section_end; section_head++)
    {
        FieldCombinationState& field_state = field_states[sections[section_head]];
        if(field_state == FCS_MINE) { section_value--; }
        else if(field_state == FCS_UNASSIGNED) { section_length++; }
    }
}

// returns true if there was a choice it could revert to
bool AlgorithmRefreshCombinations::RevertSegmentHeadToLastChoice(size_t& segment_head)
{
    //cout << "AlgorithmRefreshCombinations::RevertSegmentHeadToLastChoice()" << endl;
    if(choice_stack.empty()) { return false; }
    const unsigned int last_choice = choice_stack.back();
    choice_stack.pop_back();
    while(true)
    {
        const unsigned int last_modification = modifications_stack.back();
        FieldCombinationState& current_field_state = field_states[last_modification];

        // keep popping modifications from the stack until the last choice is found
        if(last_choice == last_modification)
        {
            // change the last choice into FCS_SAFE (it was originally FSC_MINE)
            current_field_state = FCS_SAFE;
            // don't pop_back because it is still a modification, just different
            break; 
        }
        else
        {
            if(current_field_state == FCS_MINE) { current_segment_mine_count--; }
            current_field_state = FCS_UNASSIGNED;
            // pop back to allow this field to be assigned something else
            modifications_stack.pop_back();
        }
    }
    const size_t last_choice_segment_head = segment_of_choice_stack.back();
    segment_of_choice_stack.pop_back();
    segment_head = last_choice_segment_head;
    return true;
}

void AlgorithmRefreshCombinations::TransitionFieldStateForward(const unsigned int section_field, const size_t current_segment_head, char& remaining_section_value, char& remaining_section_length)
{
    //cout << "AlgorithmRefreshCombinations::TransitionFieldStateForward()" << endl;
    FieldCombinationState& current_state = field_states[section_field];
    if(current_state != FCS_UNASSIGNED) { return; }
    if(remaining_section_value > 0)
    {
        // it's only a choice if there are more fields than remaining mines
        if(remaining_section_length > remaining_section_value)
        {
            choice_stack.push_back(section_field);
            segment_of_choice_stack.push_back(current_segment_head);
        }
        current_state = FCS_MINE;
        remaining_section_value--;
        current_segment_mine_count++;
    }
    else
    {
        current_state = FCS_SAFE;
    }
    modifications_stack.push_back(section_field);
    remaining_section_length--;
}

void AlgorithmRefreshCombinations::ApplyCurrentCombinationAsValid(const unsigned int segment_id, const long double combination_multiplier)
{
    //cout << "AlgorithmRefreshCombinations::ApplyCurrentCombinationAsValid()" << endl;
    const unsigned int final_mine_count = current_segment_mine_count;
    // store the number of combinations for the whole segment
    segments_combinations[segment_id][final_mine_count] += combination_multiplier;
    // store the number of mines in subsegments
    std::vector<SubsegmentData>& subsegments_ref = data.subsegments[segment_id];
    const size_t subsegments_max = subsegments_ref.size();
    for(size_t subsegment_id = 0; subsegment_id < subsegments_max; subsegment_id++)
    {
        SubsegmentData& subsegment_ref = subsegments_ref[subsegment_id];
        const unsigned char number_of_mines_in_subsegment = subsegment_ref.possible_values[subsegment_ref.current_possibility_id];
        // nothing to calculate or add if there are no mines in the subsegment
        if(number_of_mines_in_subsegment == 0) { continue; }
        const size_t number_of_fields_in_subsegment = subsegment_ref.fields.size();
        // confusing logic to avoid unnecessary division and/or multiplication
        const long double mines_per_field_in_subsegment = number_of_fields_in_subsegment == number_of_mines_in_subsegment
            ? combination_multiplier
            :   (
                    number_of_mines_in_subsegment == 1 
                    ? combination_multiplier / number_of_fields_in_subsegment
                    :  (combination_multiplier * number_of_mines_in_subsegment) / number_of_fields_in_subsegment
                );
        for(size_t subsegment_field_id = 0; subsegment_field_id < number_of_fields_in_subsegment; subsegment_field_id++)
        {
            const unsigned int subsegment_field = subsegment_ref.fields[subsegment_field_id];
            field_combinations_temp[subsegment_field][final_mine_count] += mines_per_field_in_subsegment;
        }
    }
    // store the number of mines for fields that are not subsegments
    std::vector<unsigned int>& segment_face = data.segments_face[segment_id];
    const unsigned int segment_face_l = segment_face.size();
    for(size_t segment_face_id = 0; segment_face_id < segment_face_l; segment_face_id++)
    {
        const unsigned int segment_face_field = segment_face[segment_face_id];
        // subsegments were already handled above
        if(data.is_subsegment[segment_face_field]) { continue; }
        // only look for the mines of this combination
        if(field_states[segment_face_field] != FCS_MINE) { continue; }
        field_combinations_temp[segment_face_field][final_mine_count] += combination_multiplier;
    }
}

bool AlgorithmRefreshCombinations::NextSubsegmentsCombination(std::vector<SubsegmentData>& subsegments_ref)
{
    //cout << "AlgorithmRefreshCombinations::NextSubsegmentsCombination()" << endl;
    // repeatedly called, this will enumerate over every possible set of values of subsegments within the segment
    // returns false if there aren't any more possibilities for the sets of values of subsegments
    const size_t subsegments_max = subsegments_ref.size();
    for(size_t subsegment_id = 0; subsegment_id < subsegments_max; subsegment_id++)
    {
        SubsegmentData& subsegment = subsegments_ref[subsegment_id];
        subsegment.current_possibility_id++;
        if(subsegment.current_possibility_id == subsegment.total_possibilities)
        {
            subsegment.current_possibility_id = 0;
            continue;
        }
        // will return true if at least one of the subsegments has not reached its max possibilities
        return true;
    }
    return false;
}

void AlgorithmRefreshCombinations::MergeAllSegmentsCombinations()
{
    //cout << "AlgorithmRefreshCombinations::MergeAllSegmentsCombinations()" << endl;
    CachePossibleSegmentsMineCounts();
    do
    {
        const unsigned int segments_combination_mine_count = GetTotalMineCountOfSegmentCombination();
        // this combination of segments has more mines than there are left on the map. it's not valid
        if(segments_combination_mine_count > remaining_mines) { continue; }
        // this combination of segments has too few mines for the remaining mines to fit 
        // in remaining non-segment covered fields. it's not valid
        if(remaining_mines - segments_combination_mine_count > remaining_fields) { continue; }
        MergeCurrentSegmentsMineCountCombination(segments_combination_mine_count);
    } while (NextSegmentsMineCountCombination());
}

void AlgorithmRefreshCombinations::CachePossibleSegmentsMineCounts()
{
    //cout << "AlgorithmRefreshCombinations::CachePossibleSegmentsMineCounts()" << endl;
    const unsigned int segments_to_check = data.segments_count;
    for(unsigned int segment_id = 0; segment_id < segments_to_check; segment_id++)
    {
        std::map<unsigned int, long double>& combinations_ref = segments_combinations[segment_id];
        if(combinations_ref.size() == 0) { cout << "segment " << segment_id << " is empty" << endl; }
        std::vector<unsigned int>& mine_counts_ref = mine_counts_in_segment[segment_id];
        for(auto it = combinations_ref.begin(); it != combinations_ref.end(); ++it)
        {
            mine_counts_ref.push_back(it->first);
        }
    }
}

unsigned int AlgorithmRefreshCombinations::GetTotalMineCountOfSegmentCombination()
{
    //cout << "AlgorithmRefreshCombinations::GetTotalMineCountOfSegmentCombination()" << endl;
    unsigned int mine_count_sum = 0;
    const size_t segments_count = data.segments_count;
    for(size_t segment_id = 0; segment_id < segments_count; segment_id++)
    {
        mine_count_sum += mine_counts_in_segment[segment_id][current_mine_count_id_in_segment[segment_id]];
    }
    return mine_count_sum;
}

void AlgorithmRefreshCombinations::MergeCurrentSegmentsMineCountCombination(const unsigned int segments_combination_mine_count)
{
    //cout << "AlgorithmRefreshCombinations::MergeCurrentSegmentsMineCountCombination()" << endl;
    long double combinations_for_current_mine_count_combination = 1.0L;
    const unsigned int mines_in_remaining_fields = remaining_mines - segments_combination_mine_count;
    const unsigned int remaining_safe_fields = remaining_fields - mines_in_remaining_fields;
    // binomial distribution of the remaining mines in the remaining fields (outside of segments)
    // f(n, k) = n! / (k! * (n - k)!)
    // using pre-calculated values for factorials and reciprocals
    combinations_for_current_mine_count_combination = 
        data.factorial[remaining_fields] * 
        data.factorial_reciprocal[mines_in_remaining_fields] * 
        data.factorial_reciprocal[remaining_safe_fields];

    const size_t segments_count = data.segments_count;
    // calculate the number of mine combinations for this combination of mine counts in the segments
    for(size_t segment_id = 0; segment_id < segments_count; segment_id++)
    {
        const size_t mine_count_id = current_mine_count_id_in_segment[segment_id];
        const unsigned int mine_count = mine_counts_in_segment[segment_id][mine_count_id];
        const long double segment_combinations_for_current_possibility = segments_combinations[segment_id][mine_count];
        combinations_for_current_mine_count_combination *= segment_combinations_for_current_possibility;
    }
    // store this number of combinations for the remaining fields
    data.remaining_fields_mine_count_combinations[segments_combination_mine_count] += combinations_for_current_mine_count_combination;
    data.total_combinations += combinations_for_current_mine_count_combination;
    for(size_t segment_id = 0; segment_id < segments_count; segment_id++)
    {
        const size_t mine_count_id = current_mine_count_id_in_segment[segment_id];
        const unsigned int mine_count = mine_counts_in_segment[segment_id][mine_count_id];
        std::vector<unsigned int>& segment_face = data.segments_face[segment_id];
        const size_t segment_face_length = segment_face.size();
        for(size_t face_field_id = 0; face_field_id < segment_face_length; face_field_id++)
        {
            const unsigned int face_field = segment_face[face_field_id];
            // check if this field ever has mines in combination containing mine_count number of mines in the segment
            if(field_combinations_temp[face_field].count(mine_count))
            {
                // if it does, add the combinations of the entire face to that field into the final map
                // for the mine count of the entire face
                data.field_combinations[face_field][segments_combination_mine_count] += combinations_for_current_mine_count_combination;
            }
        }
    }
}

bool AlgorithmRefreshCombinations::NextSegmentsMineCountCombination()
{
    //cout << "AlgorithmRefreshCombinations::NextSegmentsMineCountCombination()" << endl;
    // repeatedly called, this will enumerate over every possible set of values of mine counts within the segments
    // returns false if there aren't any more possibilities for the sets of mine counts of segments
    const size_t segments_count = data.segments_count;
    for(size_t segment_id = 0; segment_id < segments_count; segment_id++)
    {
        size_t segment_mine_counts_l = mine_counts_in_segment[segment_id].size();
        if(segment_mine_counts_l == 0) { cout << "!!!!! there are 0 mine count possibilities for segment " << segment_id << endl; }
        size_t& possibility_id = current_mine_count_id_in_segment[segment_id];
        possibility_id++;
        if(possibility_id >= segment_mine_counts_l)
        {
            possibility_id = 0;
            continue;
        }
        // will return true if at least one of the segments has not reached its max possibilities
        return true;
    }
    return false;
}
