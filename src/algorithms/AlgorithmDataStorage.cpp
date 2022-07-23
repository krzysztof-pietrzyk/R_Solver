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
    sections = std::vector<Section>(grid.S, Section());

    segments_index = 0;
    segments_count = 0;
    segments = std::vector<unsigned int>(grid.NM, 0);
    segments_starting_indexes = std::vector<unsigned int>(grid.NM, 0);
    segments_l = std::vector<unsigned int>(grid.NM, 0);

    subsegments = std::vector<std::vector<SubsegmentData>>();
    is_subsegment = std::vector<bool>(grid.S, false);
    subsegments_cache = std::vector<unsigned int>(grid.S, 0);
    subsegments_cache_index = 0;

    face = std::vector<unsigned int>(grid.S, 0);
    is_face = std::vector<bool>(grid.S, false);
    face_index = 0;
    segments_face = std::vector<std::vector<unsigned int>>(grid.M, std::vector<unsigned int>());

    factorial = std::vector<long double>(grid.S, 0.0L);
    factorial_reciprocal = std::vector<long double>(grid.S, 0.0L);

    field_combinations = std::vector<long double>(grid.S, 0.0L);
    total_combinations = 0.0L;
    remaining_fields_combinations = 0.0L;

    PreCalculateFactorials(grid);
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
    for(size_t i = 0; i < sections_origins_index; i++)
    {
        is_section_origin[sections_origins[i]] = false;
        sections[i].fields_index = 0;
        sections[i].neighbors_index = 0;
    }
    sections_origins_index = 0;
    segments_index = 0;
    segments_count = 0;
}

// only called once in constructor
void AlgorithmDataStorage::PreCalculateFactorials(GridManager& grid)
{
    long double current_factorial = 1.0L;
    long double current_factorial_reciprocal = 1.0L;
    factorial[0] = current_factorial;
    factorial_reciprocal[0] = current_factorial_reciprocal;
    for(unsigned int i = 1; i < grid.S; i++)
    {
        current_factorial *= (long double)i;
        current_factorial_reciprocal /= (long double)i;
        factorial[i] = current_factorial;
        factorial_reciprocal[i] = current_factorial_reciprocal;
    }
}
