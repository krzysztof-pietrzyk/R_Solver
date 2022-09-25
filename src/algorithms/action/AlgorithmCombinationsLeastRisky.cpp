#include "AlgorithmCombinationsLeastRisky.hpp"

AlgorithmCombinationsLeastRisky::AlgorithmCombinationsLeastRisky(GridManager& grid_, AlgorithmDataStorage& data_) : AlgorithmAction(grid_, data_) {}

AlgorithmCombinationsLeastRisky::~AlgorithmCombinationsLeastRisky() {}

AlgorithmStatus AlgorithmCombinationsLeastRisky::RunInternal()
{
    const long double total_combinations = data.total_combinations;
    const unsigned int face_length = data.face_index;
    long double lowest_combination = __LDBL_MAX__;
    unsigned int safest_field = UINT_MAX;
    // Find the safest field (lowest entry in data.field_combinations)
    for(unsigned int i = 0; i < face_length; i++)
    {
        const unsigned int face_field = data.face[i];
        const long double face_field_combinations = data.field_combinations[face_field];
        if(face_field_combinations < lowest_combination)
        {
            lowest_combination = face_field_combinations;
            safest_field = face_field;
        }
    }
    // Only click if a field was found
    if(safest_field != UINT_MAX)
    {
        grid.LeftClick(safest_field);
        return AlgorithmStatus::SUCCESS;
    }
    return AlgorithmStatus::NO_MOVES;
}
