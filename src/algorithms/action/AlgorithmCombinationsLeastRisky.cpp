#include "AlgorithmCombinationsLeastRisky.hpp"

AlgorithmCombinationsLeastRisky::AlgorithmCombinationsLeastRisky(GridManager& grid_, AlgorithmDataStorage& data_)
    : AlgorithmAction(grid_, data_), max_combinations(data.factorial.back()) {}

AlgorithmCombinationsLeastRisky::~AlgorithmCombinationsLeastRisky() {}

void AlgorithmCombinationsLeastRisky::RunInternal()
{
    const unsigned int safest_field = FindSafestField();
    // Only click if a field was found
    if(safest_field != UINT_MAX)
    {
        LeftClick(safest_field);
    }
}

unsigned int AlgorithmCombinationsLeastRisky::FindSafestField() const
{
    const unsigned int face_length = data.face_index;
    BigNum lowest_combination = max_combinations;
    unsigned int safest_field = UINT_MAX;
    // Find the safest field (index of lowest entry in data.field_combinations)
    for(size_t i = 0; i < face_length; i++)
    {
        const unsigned int face_field = data.face[i];
        const BigNum face_field_combinations = data.field_combinations[face_field];
        if(face_field_combinations < lowest_combination)
        {
            lowest_combination = face_field_combinations;
            safest_field = face_field;
        }
    }
    return safest_field;
}
