#include "AlgorithmRefreshCombinations.hpp"

AlgorithmRefreshCombinations::AlgorithmRefreshCombinations(GridAccessPlayerIf& grid_, AlgorithmDataStorage& data_)
    : Algorithm(grid_, data_),
    D_subsegments(GetModifiableAlgorithmDataStorageReference().subsegments),
    D_field_combinations(GetModifiableAlgorithmDataStorageReference().field_combinations),
    D_remaining_fields_combinations(GetModifiableAlgorithmDataStorageReference().remaining_fields_combinations),
    D_total_combinations(GetModifiableAlgorithmDataStorageReference().total_combinations)
{
    LOGGER(LOG_INIT) << "AlgorithmRefreshCombinations";
    field_states = std::vector<FieldCombinationState>(grid.GetSize(), FCS_UNASSIGNED);
    choice_stack = std::vector<uint32_t>();
    segment_of_choice_stack = std::vector<uint32_t>();
    modifications_stack = std::vector<uint32_t>();
    current_segment_mine_count = 0;
    remaining_mines = 0;
    remaining_fields = 0;

    mine_counts_in_segment = std::vector<std::vector<uint32_t>>(grid.GetTotalMines(), std::vector<uint32_t>());
    current_mine_count_id_in_segment = std::vector<size_t>(grid.GetTotalMines(), 0);

    segments_combinations = std::vector<std::map<uint32_t, BigNum>>(grid.GetTotalMines(), std::map<uint32_t, BigNum>());
    field_combinations_temp = std::vector<std::map<uint32_t, BigNum>>(grid.GetSize(), std::map<uint32_t, BigNum>());
}

AlgorithmRefreshCombinations::~AlgorithmRefreshCombinations() {}

AlgorithmStatus AlgorithmRefreshCombinations::Execution()
{
    Clear();
    remaining_mines = grid.GetTotalMines() - flagged.Index();
    remaining_fields = grid.GetSize() - visible.Index() - flagged.Index() - data.face_index;
    const uint32_t segments_to_check = data.segments_count;
    for(size_t i = 0; i < segments_to_check; i++)
    {
        FindCombinationsForSegment(i);
    }
    MergeAllSegmentsCombinations();

    return AlgorithmStatus::NO_STATUS;
}

// only called once at the beginning of Run
void AlgorithmRefreshCombinations::Clear()
{
    // Only clearing fields that are going to be used
    const uint32_t face_length = data.face_index;
    for(size_t i = 0; i < face_length; i++)
    {
        const uint32_t face_field = data.face[i];
        field_states[face_field] = FCS_UNASSIGNED;
        D_field_combinations[face_field] = 0;
        field_combinations_temp[face_field].clear();
    }
    const uint32_t segments_count = data.segments_count;
    for(size_t i = 0; i < segments_count; i++)
    {
        segments_combinations[i].clear();
        mine_counts_in_segment[i].clear();
        current_mine_count_id_in_segment[i] = 0;
    }
    D_remaining_fields_combinations = 0;
    D_total_combinations = 0.0L;
}

void AlgorithmRefreshCombinations::FindCombinationsForSegment(uint32_t segment_id)
{
    std::vector<SubsegmentData>& subsegments_ref = D_subsegments[segment_id];
    do
    {
        ClearStatesInSegment(segment_id);
        const BigNum combination_multiplier = ApplySubsegmentsCombination(subsegments_ref);
        FindCombinationsForFixedSubsegments(segment_id, combination_multiplier);
    } while (NextSubsegmentsCombination(subsegments_ref));
}

void AlgorithmRefreshCombinations::ClearStatesInSegment(uint32_t segment_id)
{
    const std::vector<uint32_t>& segment_face = data.segments_face[segment_id];
    const size_t segment_face_l = segment_face.size();
    for(size_t i = 0; i < segment_face_l; i++)
    {
        const uint32_t segment_face_field = segment_face[i];
        field_states[segment_face_field] = FCS_UNASSIGNED;
    }
}

BigNum AlgorithmRefreshCombinations::ApplySubsegmentsCombination(std::vector<SubsegmentData>& subsegments_ref)
{
    // returns the weight of the combination. it is the multiplier of the number of mine combinations
    // of the entire segment for this particular set of subsegments values combination
    current_segment_mine_count = 0;
    BigNum subsegment_combination_weight = 1;
    const size_t subsegments_max = subsegments_ref.size();
    for(size_t subsegment_id = 0; subsegment_id < subsegments_max; subsegment_id++)
    {
        SubsegmentData& subsegment = subsegments_ref[subsegment_id];
        const uint8_t mines_to_add = subsegment.possible_values[subsegment.current_possibility_id];
        subsegment_combination_weight = subsegment_combination_weight * subsegment.combinations_for_value[mines_to_add];
        const size_t subsegment_l = subsegment.fields.size();
        for(size_t i = 0; i < subsegment_l; i++)
        {
            const uint32_t subsegment_field = subsegment.fields[i];
            if(i < mines_to_add) { field_states[subsegment_field] = FCS_MINE; current_segment_mine_count++; }
            else                 { field_states[subsegment_field] = FCS_SAFE; }
        }
    }
    return subsegment_combination_weight;
}

void AlgorithmRefreshCombinations::FindCombinationsForFixedSubsegments(const uint32_t segment_id, const BigNum combination_multiplier)
{
    choice_stack.clear();
    modifications_stack.clear();
    modifications_stack.clear();
    const uint32_t segment_begin = data.segments_starting_indexes[segment_id];
    const uint32_t segment_end = segment_begin + data.segments_l[segment_id];
    size_t segment_head = segment_begin;
    // dirty loop. segment_head may be going back and forth but will always terminate
    while(true)
    {
        const uint32_t section_origin = data.segments[segment_head];
        const Section& current_section = data.sections[section_origin];
        const uint8_t section_l = current_section.fields_index;
        int8_t remaining_section_value = current_section.value;
        int8_t remaining_section_length = 0;
        FindRemainingSectionValue(current_section, remaining_section_value, remaining_section_length);
        // check if previous choices have already made this section contain a contradiction
        if(remaining_section_value < 0) 
        {
            bool revert_success = RevertSegmentHeadToLastChoice(segment_head);
            if(revert_success) { continue; }
            else               { break; }
        }

        // Apply state transitions
        for(size_t section_head = 0; section_head < section_l; section_head++)
        {
            const uint32_t section_field = current_section.fields[section_head];
            TransitionFieldStateForward(section_field, segment_head, remaining_section_value, remaining_section_length);
        }

        // check if enough mines were put into the section
        if(remaining_section_value != 0)
        {
            bool revert_success = RevertSegmentHeadToLastChoice(segment_head);
            if(revert_success) { continue; }
            else               { break; }
        }

        segment_head++;

        // if no contradictions were found until the last segment, this combination is valid
        if(segment_head == segment_end)
        {
            ApplyCurrentCombinationAsValid(segment_id, combination_multiplier);
            bool revert_success = RevertSegmentHeadToLastChoice(segment_head);
            if(revert_success) { continue; }
            else               { break; }
        }
    }
}

void AlgorithmRefreshCombinations::FindRemainingSectionValue(const Section& section, int8_t& section_value, int8_t& section_length) const
{
    const size_t section_l = section.fields_index;
    for(size_t section_head = 0; section_head < section_l; section_head++)
    {
        const FieldCombinationState& field_state = field_states[section.fields[section_head]];
        if(field_state == FCS_MINE) { section_value--; }
        else if(field_state == FCS_UNASSIGNED) { section_length++; }
    }
}

bool AlgorithmRefreshCombinations::RevertSegmentHeadToLastChoice(size_t& segment_head)
{
    // returns true if there was a choice it could revert to
    if(choice_stack.empty()) { return false; }
    const uint32_t last_choice = choice_stack.back();
    choice_stack.pop_back();
    while(true)
    {
        const uint32_t last_modification = modifications_stack.back();
        FieldCombinationState& current_field_state = field_states[last_modification];

        // keep popping modifications from the stack until the last choice is found
        if(last_choice == last_modification)
        {
            // change the last choice into FCS_SAFE (it was originally FSC_MINE)
            current_field_state = FCS_SAFE;
            current_segment_mine_count--;
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

void AlgorithmRefreshCombinations::TransitionFieldStateForward(const uint32_t section_field, const size_t current_segment_head, int8_t& remaining_section_value, int8_t& remaining_section_length)
{
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

void AlgorithmRefreshCombinations::ApplyCurrentCombinationAsValid(const uint32_t segment_id, const BigNum combination_multiplier)
{
    const uint32_t final_mine_count = current_segment_mine_count;
    // store the number of combinations for the whole segment
    segments_combinations[segment_id][final_mine_count] += combination_multiplier;
    // store the number of mines in subsegments
    const std::vector<SubsegmentData>& subsegments_ref = data.subsegments[segment_id];
    const size_t subsegments_max = subsegments_ref.size();
    for(size_t subsegment_id = 0; subsegment_id < subsegments_max; subsegment_id++)
    {
        const SubsegmentData& subsegment_ref = subsegments_ref[subsegment_id];
        const uint8_t number_of_mines_in_subsegment = subsegment_ref.possible_values[subsegment_ref.current_possibility_id];
        // nothing to calculate or add if there are no mines in the subsegment
        if(number_of_mines_in_subsegment == 0) { continue; }
        const size_t number_of_fields_in_subsegment = subsegment_ref.fields.size();
        // confusing logic to avoid unnecessary division and/or multiplication
        const BigNum mines_per_field_in_subsegment = number_of_fields_in_subsegment == number_of_mines_in_subsegment
            ? combination_multiplier
            :   (
                    number_of_mines_in_subsegment == 1 
                    ? combination_multiplier / number_of_fields_in_subsegment
                    :  (combination_multiplier * number_of_mines_in_subsegment) / number_of_fields_in_subsegment
                );
        for(size_t subsegment_field_id = 0; subsegment_field_id < number_of_fields_in_subsegment; subsegment_field_id++)
        {
            const uint32_t subsegment_field = subsegment_ref.fields[subsegment_field_id];
            field_combinations_temp[subsegment_field][final_mine_count] += mines_per_field_in_subsegment;
        }
    }
    // store the number of mines for fields that are not subsegments
    const std::vector<uint32_t>& segment_face = data.segments_face[segment_id];
    const uint32_t segment_face_l = segment_face.size();
    for(size_t segment_face_id = 0; segment_face_id < segment_face_l; segment_face_id++)
    {
        const uint32_t segment_face_field = segment_face[segment_face_id];
        // subsegments were already handled above
        if(data.is_subsegment[segment_face_field]) { continue; }
        // only look for the mines of this combination
        if(field_states[segment_face_field] != FCS_MINE) { continue; }
        field_combinations_temp[segment_face_field][final_mine_count] += combination_multiplier;
    }
}

bool AlgorithmRefreshCombinations::NextSubsegmentsCombination(std::vector<SubsegmentData>& subsegments_ref) const
{
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
    CachePossibleSegmentsMineCounts();
    do
    {
        const uint32_t segments_combination_mine_count = GetTotalMineCountOfSegmentCombination();
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
    const uint32_t segments_to_check = data.segments_count;
    for(uint32_t segment_id = 0; segment_id < segments_to_check; segment_id++)
    {
        const std::map<uint32_t, BigNum>& combinations_ref = segments_combinations[segment_id];
        std::vector<uint32_t>& mine_counts_ref = mine_counts_in_segment[segment_id];
        for(auto it = combinations_ref.begin(); it != combinations_ref.end(); ++it)
        {
            mine_counts_ref.push_back(it->first);
        }
    }
}

uint32_t AlgorithmRefreshCombinations::GetTotalMineCountOfSegmentCombination() const
{
    uint32_t mine_count_sum = 0;
    const size_t segments_count = data.segments_count;
    for(size_t segment_id = 0; segment_id < segments_count; segment_id++)
    {
        mine_count_sum += mine_counts_in_segment[segment_id][current_mine_count_id_in_segment[segment_id]];
    }
    return mine_count_sum;
}

void AlgorithmRefreshCombinations::MergeCurrentSegmentsMineCountCombination(const uint32_t segments_combination_mine_count)
{
    const uint32_t mines_in_remaining_fields = remaining_mines - segments_combination_mine_count;
    const uint32_t remaining_safe_fields = remaining_fields - mines_in_remaining_fields;
    // binomial distribution of the remaining mines in the remaining fields (outside of segments)
    // f(n, k) = n! / (k! * (n - k)!)
    // using pre-calculated values for factorials and reciprocals
    const BigNum combinations_in_remaining_fields = 
        data.factorial[remaining_fields] * 
        data.factorial_reciprocal[mines_in_remaining_fields] * 
        data.factorial_reciprocal[remaining_safe_fields];
    // store this number of combinations for the remaining fields
    if(remaining_fields != 0)
    {
        D_remaining_fields_combinations += combinations_in_remaining_fields * (mines_in_remaining_fields / remaining_fields);
    }
    
    // initial multiplier for the combinations on the face
    BigNum combinations_for_current_mine_count_combination = combinations_in_remaining_fields;

    const size_t segments_count = data.segments_count;
    // calculate the number of mine combinations for this combination of mine counts in the segments
    for(size_t segment_id = 0; segment_id < segments_count; segment_id++)
    {
        const size_t mine_count_id = current_mine_count_id_in_segment[segment_id];
        const uint32_t mine_count = mine_counts_in_segment[segment_id][mine_count_id];
        const BigNum segment_combinations_for_current_possibility = segments_combinations[segment_id][mine_count];
        combinations_for_current_mine_count_combination *= segment_combinations_for_current_possibility;
    }

    D_total_combinations += combinations_for_current_mine_count_combination;
    for(size_t segment_id = 0; segment_id < segments_count; segment_id++)
    {
        const size_t mine_count_id = current_mine_count_id_in_segment[segment_id];
        const uint32_t mine_count = mine_counts_in_segment[segment_id][mine_count_id];
        const BigNum mine_count_combinations_in_segment = segments_combinations[segment_id][mine_count];
        const std::vector<uint32_t>& segment_face = data.segments_face[segment_id];
        const size_t segment_face_length = segment_face.size();
        for(size_t face_field_id = 0; face_field_id < segment_face_length; face_field_id++)
        {
            const uint32_t face_field = segment_face[face_field_id];
            // check if this field ever has mines in combination containing mine_count number of mines in the segment
            if(field_combinations_temp[face_field].count(mine_count))
            {
                const BigNum face_field_combinations = field_combinations_temp[face_field][mine_count];
                // how many times this field is a mine, within all combinations of this mine count in this segment
                // should be between 0 and 1 (including 0 and 1);
                const BigNum appearance_ratio = face_field_combinations / mine_count_combinations_in_segment;
                D_field_combinations[face_field] += combinations_for_current_mine_count_combination * appearance_ratio;
            }
        }
    }
}

bool AlgorithmRefreshCombinations::NextSegmentsMineCountCombination()
{
    // repeatedly called, this will enumerate over every possible set of values of mine counts within the segments
    // returns false if there aren't any more possibilities for the sets of mine counts of segments
    const size_t segments_count = data.segments_count;
    for(size_t segment_id = 0; segment_id < segments_count; segment_id++)
    {
        size_t segment_mine_counts_l = mine_counts_in_segment[segment_id].size();
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
