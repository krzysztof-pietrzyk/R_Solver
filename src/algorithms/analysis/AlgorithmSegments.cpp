// implemented header
#include "AlgorithmSegments.hpp"

// project includes
#include "../data/Section.hpp"

// std includes


AlgorithmSegments::AlgorithmSegments(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : AlgorithmAnalysis(grid_, data_),
    sections_dto(data_.sections_dto),
    segments_dto(data_.segments_dto)
{
    LOGGER(LogLevel::INIT) << "AlgorithmSegments";
    fields_to_check = std::vector<uint32_t>(grid_dim.size, 0);
    fields_to_check_index = 0;
    is_checked = std::vector<bool>(grid_dim.size, false);
}

AlgorithmSegments::~AlgorithmSegments() {}

AlgorithmStatus AlgorithmSegments::Execution()
{
    const uint32_t sections_origins_index = sections_dto.sections_origins.Index();
    Clear();

    // Go through each section origin
    for(size_t i = 0; i < sections_origins_index; i++)
    {
        const uint32_t current_section_origin = sections_dto.sections_origins[i];
        // If the field hasn't been marked as checked ...
        if(is_checked[current_section_origin]) { continue; }
        // ... start a chain reaction, which marks all section fields connected to it
        ChainReactionFromField(current_section_origin);
    }
    return AlgorithmStatus::NO_STATUS;
}

void AlgorithmSegments::Clear()
{
    for(size_t i = 0; i < fields_to_check_index; i++) { is_checked[fields_to_check[i]] = false; }
    fields_to_check_index = 0;
    segments_dto.Clear();
}

void AlgorithmSegments::ChainReactionFromField(uint32_t field)
{
    if(!sections_dto.sections_origins.Contains(field)) { return; }
    const uint32_t fields_to_check_starting_index = fields_to_check_index;
    // Initial field to start the chain reaction from
    fields_to_check[fields_to_check_index++] = field;
    is_checked[field] = true;
    segments_dto.AddField(field);
    // fields_to_check_index may increase within the runtime of this loop
    for(size_t i = fields_to_check_starting_index; i < fields_to_check_index; i++)
    {
        const uint32_t field_to_check = fields_to_check[i];
        const Section& section_to_check = sections_dto.sections[field_to_check];
        const uint8_t field_to_check_neighbors_l = section_to_check.neighbors_index;
        for(size_t j = 0; j < field_to_check_neighbors_l; j++)
        {
            const uint32_t neighbor_to_add = section_to_check.neighbors[j];
            if(!sections_dto.sections_origins.Contains(neighbor_to_add)) { continue; }  // Ignore fields that are not sections origins
            if(is_checked[neighbor_to_add]) { continue; }  // Ignore duplicates
            is_checked[neighbor_to_add] = true;
            fields_to_check[fields_to_check_index++] = neighbor_to_add;
            segments_dto.AddField(neighbor_to_add);
        }
    }
    uint32_t segment_start = fields_to_check_starting_index;
    uint32_t segment_length = fields_to_check_index - fields_to_check_starting_index;
    segments_dto.AddSegment(segment_start, segment_length);
}
