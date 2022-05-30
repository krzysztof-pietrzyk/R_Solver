#include "AlgorithmSureMovesFromCombinations.hpp"

AlgorithmSureMovesFromCombinations::AlgorithmSureMovesFromCombinations(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_, data_) {}

AlgorithmSureMovesFromCombinations::~AlgorithmSureMovesFromCombinations() {}

bool AlgorithmSureMovesFromCombinations::Run()
{
    bool success = false;
    if(grid.is_lost) return false;
    const long double total_combinations = data.total_combinations;
    const unsigned int face_length = data.face_index;
    for(unsigned int i = 0; i < face_length; i++)
    {
        const unsigned int face_field = data.face[i];
        const long double face_field_combinations = data.field_combinations[face_field];
        if(face_field_combinations == 0.0L) 
        {
            grid.LeftClick(face_field);
            success = true;
        }
        else if(face_field_combinations == total_combinations)
        {
            grid.RightClick(face_field);
            success = true;
        }
    }

    return success;
}
