#include "AlgorithmCombinationsLeastRisky.hpp"

AlgorithmCombinationsLeastRisky::AlgorithmCombinationsLeastRisky(GridManager& grid_, AlgorithmDataStorage& data_)
    : AlgorithmAction(grid_, data_),
    face(data.face), field_combinations(data.field_combinations) {}

AlgorithmCombinationsLeastRisky::~AlgorithmCombinationsLeastRisky() {}

void AlgorithmCombinationsLeastRisky::RunInternal()
{
    const unsigned int safest_field = FindSafestField();
    // Only click if a field was found
    if(safest_field != UINT_MAX)
    {
        grid.LeftClick(safest_field);
    }
}

unsigned int AlgorithmCombinationsLeastRisky::FindSafestField() const
{
    const unsigned int face_length = data.face_index;
    long double lowest_combination = __LDBL_MAX__;
    unsigned int safest_field = UINT_MAX;
    // Find the safest field (index of lowest entry in data.field_combinations)
    for(size_t i = 0; i < face_length; i++)
    {
        const unsigned int face_field = face[i];
        const long double face_field_combinations = field_combinations[face_field];
        if(face_field_combinations < lowest_combination)
        {
            lowest_combination = face_field_combinations;
            safest_field = face_field;
        }
    }
    return safest_field;
}
