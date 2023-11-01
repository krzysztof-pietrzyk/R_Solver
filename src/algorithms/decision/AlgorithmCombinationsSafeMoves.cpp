// implemented header
#include "AlgorithmCombinationsSafeMoves.hpp"

// project includes

// std includes


AlgorithmCombinationsSafeMoves::AlgorithmCombinationsSafeMoves(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : AlgorithmDecision(grid_, data_),
    face_dto(data_.face_dto),
    combinations_dto(data_.combinations_dto)
{
    LOGGER(LogLevel::INIT) << "AlgorithmCombinationsSafeMoves";
}

AlgorithmCombinationsSafeMoves::~AlgorithmCombinationsSafeMoves() {}

AlgorithmStatus AlgorithmCombinationsSafeMoves::Execution()
{
    const BigNum total_combinations = combinations_dto.total_combinations;
    const uint32_t face_length = face_dto.face.Index();
    const BigNum no_combinations = 0;
    for(size_t i = 0; i < face_length; i++)
    {
        const uint32_t face_field = face_dto.face[i];
        const BigNum face_field_combinations = combinations_dto.field_combinations[face_field];
        if(face_field_combinations == no_combinations) 
        {
            // A mine on this field appears in 0 combinations - it's safe
            QueueAction(face_field, PlayerAction::LEFT_CLICK);
        }
        else if(face_field_combinations == total_combinations)
        {
            // A mine on this field appears in all combinations - it's a mine
            QueueAction(face_field, PlayerAction::RIGHT_CLICK);
        }
    }

    return AlgorithmStatus::NO_STATUS;
}
