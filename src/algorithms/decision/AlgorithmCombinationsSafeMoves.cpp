#include "AlgorithmCombinationsSafeMoves.hpp"

AlgorithmCombinationsSafeMoves::AlgorithmCombinationsSafeMoves(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : AlgorithmDecision(grid_, data_)
{
    LOGGER(LogLevel::INIT) << "AlgorithmCombinationsSafeMoves";
}

AlgorithmCombinationsSafeMoves::~AlgorithmCombinationsSafeMoves() {}

AlgorithmStatus AlgorithmCombinationsSafeMoves::Execution()
{
    const BigNum total_combinations = data.total_combinations;
    const uint32_t face_length = data.face_index;
    const BigNum no_combinations = 0;
    for(size_t i = 0; i < face_length; i++)
    {
        const uint32_t face_field = data.face[i];
        const BigNum face_field_combinations = data.field_combinations[face_field];
        if(face_field_combinations == no_combinations) 
        {
            // A mine on this field appears in 0 combinations - it's safe
            LeftClick(face_field);
        }
        else if(face_field_combinations == total_combinations)
        {
            // A mine on this field appears in all combinations - it's a mine
            RightClick(face_field);
        }
    }

    return AlgorithmStatus::NO_STATUS;
}
