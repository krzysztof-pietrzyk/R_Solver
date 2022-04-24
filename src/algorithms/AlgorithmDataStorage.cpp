#include "AlgorithmDataStorage.hpp"

AlgorithmDataStorage::AlgorithmDataStorage(GridManager& grid)
{
    is_border = std::vector<bool>(grid.S, false);
    border_internal_0 = std::vector<unsigned int>(grid.S, 0);
    border_internal_1 = std::vector<unsigned int>(grid.S, 0);
    border_internal_indicator = false;
    border_index = 0;
    last_read_index_border = 0;
    last_read_index_border_flags = 0;

    sections_origins_index = 0;
    sections_origins = std::vector<unsigned int>(grid.S, 0);
    is_section_origin = std::vector<bool>(grid.S, false);
    sections = std::vector<unsigned int>(grid.S * MAX_SECTION_LENGTH, 0);
    sections_l = std::vector<unsigned char>(grid.S, 0);
    sections_values = std::vector<unsigned char>(grid.S, 0);
    sections_neighbors = std::vector<unsigned int>(grid.S * MAX_SECTION_NEIGHBORS, 0);
    sections_neighbors_l = std::vector<unsigned char>(grid.S, 0);

    segments_index = 0;
    segments_count = 0;
    segments = std::vector<unsigned int>(grid.S, 0);
    segments_starting_indexes = std::vector<unsigned int>(grid.S, 0);
    segments_l = std::vector<unsigned int>(grid.S, 0);
}

AlgorithmDataStorage::~AlgorithmDataStorage() {}

std::vector<unsigned int>& AlgorithmDataStorage::GetBorder()
{
    if(border_internal_indicator) { return border_internal_0; }
    else { return border_internal_1; }
}

void AlgorithmDataStorage::Clear()
{
    const std::vector<unsigned int>& border = GetBorder();
    for(size_t i = 0; i < border_index; i++) is_border[border[i]] = false;
    border_index = 0;
    last_read_index_border = 0;
    last_read_index_border_flags = 0;
    for(size_t i = 0; i < sections_origins_index; i++) is_section_origin[sections_origins[i]] = false;
    sections_origins_index = 0;
    segments_index = 0;
    segments_count = 0;
}
