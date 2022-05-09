#include "AlgorithmOptimizedSegments.hpp"

AlgorithmOptimizedSegments::AlgorithmOptimizedSegments(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_, data_)
{
    is_checked = std::vector<bool>(grid.S, false);
    checked = std::vector<unsigned int>(grid.S, 0);
    checked_index = 0;
    neighbors_bits = std::map<unsigned int, unsigned int>();
    section_neighborhood = std::map<unsigned int, std::vector<unsigned int>>();
}

AlgorithmOptimizedSegments::~AlgorithmOptimizedSegments() {}

bool AlgorithmOptimizedSegments::Run()
{
    Clear();

    const unsigned int segments_count = data.segments_count;

    for(size_t segment_id = 0; segment_id < segments_count; segment_id++)
    {
        data.optimized_segments.push_back(std::vector<OptimizedSegmentData>());
        // It's important to keep track which segment this optimization relates to
        // This is why we are iterating over segments, not over sections directly
        const unsigned int segment_begin = data.segments_starting_indexes[segment_id];
        const unsigned int segment_end = segment_begin + data.segments_l[segment_id];
        for(size_t j = segment_begin; j < segment_end; j++)
        {
            // Border fields are unique in segments. No need to check for duplicates here
            const unsigned int border_field = data.segments[j];
            UpdateNeighborsBits(border_field);
            UpdateSectionNeighborhood(border_field);
            FindSegmentsToOptimize(segment_id);
        }
    }

    return true;
}

void AlgorithmOptimizedSegments::Clear()
{
    for(size_t i = 0; i < checked_index; i++) { is_checked[checked[i]] = false; }
    checked_index = 0;
    data.optimized_segments.clear();
}

void AlgorithmOptimizedSegments::UpdateNeighborsBits(unsigned int border_field)
{
    neighbors_bits.clear();
    const unsigned int border_field_neighbors_begin = border_field * MAX_SECTION_NEIGHBORS;
    const unsigned int border_field_neighbors_end = border_field_neighbors_begin + data.sections_neighbors_l[border_field];
    unsigned int bit_shift_temp = 1;
    for(size_t i = border_field_neighbors_begin; i < border_field_neighbors_end; i++)
    {
        // border_field_neighbors are origins of sections, which overlap with this border field's section
        // each of those neighbors is being assigned a different bit.
        // those bits will be later summed up to create a hash of section field's neighbors
        const unsigned int border_field_neighbor = data.sections_neighbors[i];
        neighbors_bits[border_field_neighbor] = bit_shift_temp;
        bit_shift_temp = bit_shift_temp << 1;
    }
}

void AlgorithmOptimizedSegments::UpdateSectionNeighborhood(unsigned int section_origin)
{
    section_neighborhood.clear();
    const unsigned int section_start = section_origin * MAX_SECTION_LENGTH;
    const unsigned int section_end = section_start + data.sections_l[section_origin];
    for(size_t i = section_start; i < section_end; i++)
    {
        const unsigned int section_field = data.sections[i];
        // Sections can overlap. Need to check for duplicates
        if(is_checked[section_field]) { continue; }
        is_checked[section_field] = true;
        checked[checked_index++] = section_field;
        const unsigned int section_field_neighborhood_hash = GetNeighborhoodHash(section_field);
        if(section_neighborhood.count(section_field_neighborhood_hash) == 0)
        {
            // first time this hash appears for this section. create an empty vector
            section_neighborhood[section_field_neighborhood_hash] = std::vector<unsigned int>();
        }
        // if a hash appears more than once in a section, push back to the existing vector
        section_neighborhood[section_field_neighborhood_hash].push_back(section_field);
    }
}

void AlgorithmOptimizedSegments::FindSegmentsToOptimize(unsigned int parent_segment)
{
    for(auto iter = section_neighborhood.begin(); iter != section_neighborhood.end(); ++iter)
    {
        const size_t hash_repetitions = iter->second.size();
        // filter out all hashes which appear less than 2 times (vast majority)
        if(hash_repetitions < 2) { continue; }
        OptimizedSegmentData subsegment_temp = OptimizedSegmentData();
        // copy the fields into the structure
        for(size_t i = 0; i < hash_repetitions; i++) { subsegment_temp.fields.push_back(iter->second[i]); }
        FindPossibleValuesForSubsegment(subsegment_temp);
        data.optimized_segments[parent_segment].push_back(subsegment_temp);
    }
}

unsigned int AlgorithmOptimizedSegments::GetNeighborhoodHash(unsigned int section_field)
{
    const unsigned int section_field_neighbors_begin = section_field * grid.MAX_NEIGHBORS;
    const unsigned int section_field_neighbors_end = section_field_neighbors_begin + grid.neighbors_l[section_field];
    unsigned int hash_result = 0;
    for(size_t i = section_field_neighbors_begin; i < section_field_neighbors_end; i++)
    {
        const unsigned int section_field_neighbor = grid.neighbors[i];
        // only consider fields that are section origins
        if(!data.is_section_origin[section_field_neighbor]) { continue; }
        hash_result += neighbors_bits[section_field_neighbor];
    }
    return hash_result;
}

void AlgorithmOptimizedSegments::FindPossibleValuesForSubsegment(OptimizedSegmentData& subsegment_data)
{
    // all subsegment fields have the same neighboring section origins. just take the first one
    const unsigned int subsegment_field = subsegment_data.fields[0];
    const unsigned int subsegment_field_neighbors_begin = subsegment_field * grid.MAX_NEIGHBORS;
    const unsigned int subsegment_field_neighbors_end = subsegment_field_neighbors_begin + grid.neighbors_l[subsegment_field];
    const size_t subsegment_length = subsegment_data.fields.size();
    unsigned char minimum_section_value = UCHAR_MAX;
    char maximum_forced_mines = 0;
    for(size_t i = subsegment_field_neighbors_begin; i < subsegment_field_neighbors_end; i++)
    {
        const unsigned int subsegment_field_neighbor = grid.neighbors[i];
        // ignore neighbors which are not section origins
        if(!data.is_section_origin[subsegment_field_neighbor]) { continue; }
        const unsigned char section_value = data.sections_values[subsegment_field_neighbor];
        const unsigned char section_length = data.sections_l[subsegment_field_neighbor];
        // will be greater than 0 if the section value is so big that it can't fit
        // in the section without allocating at least one mine in the subsegment
        const char forced_mines = section_value - section_length + subsegment_length;
        // find the smallest section value, out of the sections containing this subsegment
        // this will be the upper bound for the number of mines in this subsegment
        if(section_value < minimum_section_value) { minimum_section_value = section_value; }
        // find the biggest number of forced mines in this subsegment
        // this will be the lower bound for the number of mines in this subsegment
        if(forced_mines > maximum_forced_mines) { maximum_forced_mines = forced_mines; }
    }
    // a little paranoid check. maximum_forced_mines should never be less than 0 anyways
    const unsigned char lower_bound = maximum_forced_mines > 0 ? maximum_forced_mines : 0;
    // there can't be more mines in the subsegment than there are fields in the subsegment
    const unsigned char upper_bound = minimum_section_value < subsegment_length ? minimum_section_value : subsegment_length;
    // all values between those bounds are possible numbers of mines in this subsection (including bounds)
    for(unsigned char i = lower_bound; i <= upper_bound; i++)
    {
        subsegment_data.possible_values.push_back(i);
    }
}

unsigned int AlgorithmOptimizedSegments::NChooseK(unsigned int n, unsigned int k)
{
    // vast majority of results are handled by those two cases
    if(k == 0 || k == n) { return 1; }
    else if(k == 1 || k == n - 1) { return n; }
    // less popular cases (exhaustive list)
    else if(n == 4 && k == 2) { return 6; }
    else if(n == 5 && (k == 2 || k == 3)) { return 10; }
    else if(n == 6)
    {
        if(k == 2 || k == 4) { return 15; }
        else if(k == 3) { return 20; }
    }
    else if(n == 7)
    {
        if(k == 2 || k == 5) { return 21; }
        else if(k == 3 || k == 4) { return 35; }
    }
    else if(n == 8)
    {
        if(k == 2 || k == 6) { return 28; }
        else if(k == 3 || k == 5) { return 56; }
        else if(k == 4) { return 70; }
    }
    // else do full computation? throw exception?
    return 0;
}
