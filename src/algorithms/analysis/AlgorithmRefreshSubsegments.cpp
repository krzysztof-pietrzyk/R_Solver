#include "AlgorithmRefreshSubsegments.hpp"

AlgorithmRefreshSubsegments::AlgorithmRefreshSubsegments(GridAccessPlayerIf& grid_, AlgorithmDataStorage& data_)
    : Algorithm(grid_, data_),
    D_subsegments(GetModifiableAlgorithmDataStorageReference().subsegments),
    D_is_subsegment(GetModifiableAlgorithmDataStorageReference().is_subsegment),
    D_subsegments_cache(GetModifiableAlgorithmDataStorageReference().subsegments_cache),
    D_subsegments_cache_index(GetModifiableAlgorithmDataStorageReference().subsegments_cache_index)
{
    LOGGER(LOG_INIT) << "AlgorithmRefreshSubsegments";
    is_checked = std::vector<bool>(grid.GetSize(), false);
    checked = std::vector<uint32_t>(grid.GetSize(), 0);
    checked_index = 0;
    neighbors_bits = std::map<uint32_t, uint32_t>();
    section_neighborhood = std::map<uint32_t, std::vector<uint32_t>>();
}

AlgorithmRefreshSubsegments::~AlgorithmRefreshSubsegments() {}

AlgorithmStatus AlgorithmRefreshSubsegments::Execution()
{
    Clear();

    const uint32_t segments_count = data.segments_count;

    for(size_t segment_id = 0; segment_id < segments_count; segment_id++)
    {
        D_subsegments.push_back(std::vector<SubsegmentData>());
        // It's important to keep track which segment this optimization relates to
        // This is why we are iterating over segments, not over sections directly
        const uint32_t segment_begin = data.segments_starting_indexes[segment_id];
        const uint32_t segment_end = segment_begin + data.segments_l[segment_id];
        for(size_t j = segment_begin; j < segment_end; j++)
        {
            // Border fields are unique in segments. No need to check for duplicates here
            const uint32_t border_field = data.segments[j];
            UpdateNeighborsBits(border_field);
            UpdateSectionNeighborhood(border_field);
            FindSegmentsToOptimize(segment_id);
        }
    }

    return AlgorithmStatus::NO_STATUS;
}

void AlgorithmRefreshSubsegments::Clear()
{
    for(size_t i = 0; i < checked_index; i++) { is_checked[checked[i]] = false; }
    checked_index = 0;
    const uint32_t subsegments_cache_index = data.subsegments_cache_index;
    for(size_t i = 0; i < subsegments_cache_index; i++) { D_is_subsegment[data.subsegments_cache[i]] = false; }
    D_subsegments_cache_index = 0;
    D_subsegments.clear();
}

void AlgorithmRefreshSubsegments::UpdateNeighborsBits(const uint32_t border_field)
{
    neighbors_bits.clear();
    const Section& border_field_section = data.sections[border_field];
    const size_t border_field_neighbors_l = border_field_section.neighbors_index;
    uint32_t bit_shift_temp = 1;
    for(size_t i = 0; i < border_field_neighbors_l; i++)
    {
        // border_field_neighbors are origins of sections, which overlap with this border field's section
        // each of those neighbors is being assigned a different bit.
        // those bits will be later summed up to create a hash of section field's neighbors
        const uint32_t border_field_neighbor = border_field_section.neighbors[i];
        neighbors_bits[border_field_neighbor] = bit_shift_temp;
        bit_shift_temp = bit_shift_temp << 1;
    }
}

void AlgorithmRefreshSubsegments::UpdateSectionNeighborhood(const uint32_t section_origin)
{
    section_neighborhood.clear();
    const Section& current_section = data.sections[section_origin];
    const size_t current_section_l = current_section.fields_index;
    for(size_t i = 0; i < current_section_l; i++)
    {
        const uint32_t section_field = current_section.fields[i];
        // Sections can overlap. Need to check for duplicates
        if(is_checked[section_field]) { continue; }
        is_checked[section_field] = true;
        checked[checked_index++] = section_field;
        const uint32_t section_field_neighborhood_hash = GetNeighborhoodHash(section_field);
        if(section_neighborhood.count(section_field_neighborhood_hash) == 0)
        {
            // first time this hash appears for this section. create an empty vector
            section_neighborhood[section_field_neighborhood_hash] = std::vector<uint32_t>();
        }
        // if a hash appears more than once in a section, push back to the existing vector
        section_neighborhood[section_field_neighborhood_hash].push_back(section_field);
    }
}

void AlgorithmRefreshSubsegments::FindSegmentsToOptimize(const uint32_t parent_segment) const
{
    for(auto iter = section_neighborhood.begin(); iter != section_neighborhood.end(); ++iter)
    {
        const size_t hash_repetitions = iter->second.size();
        // filter out all hashes which appear less than 2 times (vast majority)
        if(hash_repetitions < 2) { continue; }
        SubsegmentData subsegment_temp = SubsegmentData();
        // copy the fields into the structure
        for(size_t i = 0; i < hash_repetitions; i++)
        {
            const uint32_t field_temp = iter->second[i];
            D_is_subsegment[field_temp] = true;
            D_subsegments_cache[D_subsegments_cache_index++] = field_temp;
            subsegment_temp.fields.push_back(field_temp); 
        }
        FindPossibleValuesForSubsegment(subsegment_temp);
        D_subsegments[parent_segment].push_back(subsegment_temp);
    }
}

uint32_t AlgorithmRefreshSubsegments::GetNeighborhoodHash(const uint32_t section_field)
{
    uint32_t hash_result = 0;
    for(const uint32_t& section_field_neighbor : grid.GetNeighbors(section_field))
    {
        // only consider fields that are section origins
        if(!data.is_section_origin[section_field_neighbor]) { continue; }
        hash_result += neighbors_bits[section_field_neighbor];
    }
    return hash_result;
}

void AlgorithmRefreshSubsegments::FindPossibleValuesForSubsegment(SubsegmentData& subsegment_data) const
{
    // all subsegment fields have the same neighboring section origins. just take the first one
    const uint32_t subsegment_field = subsegment_data.fields[0];
    const size_t subsegment_length = subsegment_data.fields.size();
    uint8_t minimum_section_value = UCHAR_MAX;
    int8_t maximum_forced_mines = 0;
    for(const uint32_t& subsegment_field_neighbor : grid.GetNeighbors(subsegment_field))
    {
        // ignore neighbors which are not section origins
        if(!data.is_section_origin[subsegment_field_neighbor]) { continue; }
        const Section& current_section = data.sections[subsegment_field_neighbor];
        const uint8_t section_value = current_section.value;
        const size_t section_length = current_section.fields_index;
        // will be greater than 0 if the section value is so big that it can't fit
        // in the section without allocating at least one mine in the subsegment
        const int8_t forced_mines = section_value - section_length + subsegment_length;
        // find the smallest section value, out of the sections containing this subsegment
        // this will be the upper bound for the number of mines in this subsegment
        if(section_value < minimum_section_value) { minimum_section_value = section_value; }
        // find the biggest number of forced mines in this subsegment
        // this will be the lower bound for the number of mines in this subsegment
        if(forced_mines > maximum_forced_mines) { maximum_forced_mines = forced_mines; }
    }
    // a little paranoid check. maximum_forced_mines should never be less than 0 anyways
    const uint8_t lower_bound = maximum_forced_mines > 0 ? maximum_forced_mines : 0;
    // there can't be more mines in the subsegment than there are fields in the subsegment
    const uint8_t upper_bound = minimum_section_value < subsegment_length ? minimum_section_value : subsegment_length;
    // all values between those bounds are possible numbers of mines in this subsection (including bounds)
    for(uint8_t i = lower_bound; i <= upper_bound; i++)
    {
        subsegment_data.possible_values.push_back(i);
        subsegment_data.combinations_for_value[i] = NChooseK(subsegment_length, i);
    }
    subsegment_data.total_possibilities = subsegment_data.possible_values.size();
    subsegment_data.current_possibility_id = 0;
}

uint32_t AlgorithmRefreshSubsegments::NChooseK(const uint32_t n, const uint32_t k) const
{
    // look-up table to speed things up. there are relatively few possible cases here
    // vast majority of results are handled by those two cases
    if(k == 0 || k == n) { return 1; }
    else if(k == 1 || k == n - 1) { return n; }
    // less popular cases (exhaustive list)
    else if(n == 4 && k == 2) { return 6; }  // only checking k value for error detection
    else if(n == 5 && (k == 2 || k == 3)) { return 10; }  // only checking k value for error detection
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
    throw std::invalid_argument("ERROR: AlgorithmRefreshSubsegments::NChooseK(n, k): Unknown result for given n, k values!");
    return 0;
}
