#include "AlgorithmRefreshSegments.hpp"

AlgorithmRefreshSegments::AlgorithmRefreshSegments(GridManager& grid_, AlgorithmDataStorage& data_)
    : Algorithm(grid_, data_),
    D_segments_index(GetModifiableAlgorithmDataStorageReference().segments_index),
    D_segments_count(GetModifiableAlgorithmDataStorageReference().segments_count),
    D_segments(GetModifiableAlgorithmDataStorageReference().segments),
    D_segments_starting_indexes(GetModifiableAlgorithmDataStorageReference().segments_starting_indexes),
    D_segments_l(GetModifiableAlgorithmDataStorageReference().segments_l)
{
    fields_to_check = std::vector<uint32_t>(grid.S, 0);
    fields_to_check_index = 0;
    is_checked = std::vector<bool>(grid.S, false);
}

AlgorithmRefreshSegments::~AlgorithmRefreshSegments() {}

AlgorithmStatus AlgorithmRefreshSegments::Run()
{
    const uint32_t sections_origins_index = data.sections_origins_index;
    Clear();

    // Go through each section origin
    for(size_t i = 0; i < sections_origins_index; i++)
    {
        const uint32_t current_section_origin = data.sections_origins[i];
        // If the field hasn't been marked as checked ...
        if(is_checked[current_section_origin]) { continue; }
        // ... start a chain reaction, which marks all section fields connected to it
        ChainReactionFromField(current_section_origin);
    }
    return AlgorithmStatus::NO_STATUS;
}

void AlgorithmRefreshSegments::Clear()
{
    for(size_t i = 0; i < fields_to_check_index; i++) { is_checked[fields_to_check[i]] = false; }
    fields_to_check_index = 0;
    D_segments_count = 0;
    D_segments_index = 0;
}

void AlgorithmRefreshSegments::ChainReactionFromField(uint32_t field)
{
    if(!data.is_section_origin[field]) return;
    const uint32_t fields_to_check_starting_index = fields_to_check_index;
    // Initial field to start the chain reaction from
    fields_to_check[fields_to_check_index++] = field;
    is_checked[field] = true;
    D_segments[D_segments_index++] = field;
    // fields_to_check_index may increase within the runtime of this loop
    for(size_t i = fields_to_check_starting_index; i < fields_to_check_index; i++)
    {
        const uint32_t field_to_check = fields_to_check[i];
        const Section& section_to_check = data.sections[field_to_check];
        const uint8_t field_to_check_neighbors_l = section_to_check.neighbors_index;
        for(size_t j = 0; j < field_to_check_neighbors_l; j++)
        {
            const uint32_t neighbor_to_add = section_to_check.neighbors[j];
            if(!data.is_section_origin[neighbor_to_add]) { continue; }  // Ignore fields that are not sections origins
            if(is_checked[neighbor_to_add]) { continue; }  // Ignore duplicates
            is_checked[neighbor_to_add] = true;
            fields_to_check[fields_to_check_index++] = neighbor_to_add;
            D_segments[D_segments_index++] = neighbor_to_add;
        }
    }
    // Save the starting index of this segment (index in data.segments[])
    D_segments_starting_indexes[data.segments_count] = fields_to_check_starting_index;
    // Save how many sections origins there are in this segment
    D_segments_l[data.segments_count] = fields_to_check_index - fields_to_check_starting_index;
    // Increment the number of segments
    D_segments_count++;
}
