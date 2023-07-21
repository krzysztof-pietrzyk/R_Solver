#include "AlgorithmDataStorage.hpp"

AlgorithmDataStorage::AlgorithmDataStorage(GridAccessPlayerIf& grid)
{
    LOGGER(LOG_INIT) << "AlgorithmDataStorage";
    is_border = std::vector<bool>(grid.GetSize(), false);
    border = std::vector<uint32_t>(grid.GetSize(), 0);
    border_index = 0;
    border_last_visible_fields_index = 0;

    sections_origins_index = 0;
    sections_origins = std::vector<uint32_t>(grid.GetSize(), 0);
    is_section_origin = std::vector<bool>(grid.GetSize(), false);
    sections = std::vector<Section>(grid.GetSize(), Section());

    segments_index = 0;
    segments_count = 0;
    segments = std::vector<uint32_t>(grid.GetTotalSafeFields(), 0);
    segments_starting_indexes = std::vector<uint32_t>(grid.GetTotalSafeFields(), 0);
    segments_l = std::vector<uint32_t>(grid.GetTotalSafeFields(), 0);

    subsegments = std::vector<std::vector<SubsegmentData>>();
    is_subsegment = std::vector<bool>(grid.GetSize(), false);
    subsegments_cache = std::vector<uint32_t>(grid.GetSize(), 0);
    subsegments_cache_index = 0;

    face = std::vector<uint32_t>(grid.GetSize(), 0);
    is_face = std::vector<bool>(grid.GetSize(), false);
    face_index = 0;
    segments_face = std::vector<std::vector<uint32_t>>(grid.GetTotalMines(), std::vector<uint32_t>());

    factorial = std::vector<BigNum>(grid.GetSize(), BigNum(0));
    factorial_reciprocal = std::vector<BigNum>(grid.GetSize(), BigNum(0));

    field_combinations = std::vector<BigNum>(grid.GetSize(), BigNum(0));
    total_combinations = BigNum(0);
    remaining_fields_combinations = BigNum(0);

    PreCalculateFactorials(grid.GetSize());
}

AlgorithmDataStorage::~AlgorithmDataStorage() {}

void AlgorithmDataStorage::Clear()
{
    for(size_t i = 0; i < border_index; i++) is_border[border[i]] = false;
    border_index = 0;
    border_last_visible_fields_index = 0;
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
void AlgorithmDataStorage::PreCalculateFactorials(uint32_t grid_size)
{
    BigNum current_factorial = BigNum(1);
    BigNum current_factorial_reciprocal = BigNum(1);
    factorial[0] = current_factorial;
    factorial_reciprocal[0] = current_factorial_reciprocal;
    for(uint32_t i = 1; i < grid_size; i++)
    {
        current_factorial *= i;
        current_factorial_reciprocal /= i;
        factorial[i] = current_factorial;
        factorial_reciprocal[i] = current_factorial_reciprocal;
    }
}
