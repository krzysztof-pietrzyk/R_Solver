#include "AlgorithmCombinationsLeastRisky.hpp"

AlgorithmCombinationsLeastRisky::AlgorithmCombinationsLeastRisky(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : AlgorithmDecision(grid_, data_),
    face_dto(data_.face_dto),
    combinations_dto(data_.combinations_dto),
    max_combinations(data_.factorials_dto.factorial.back())
{
    LOGGER(LogLevel::INIT) << "AlgorithmCombinationsLeastRisky";
    algorithm_type = AlgorithmType::COMBINATIONS_LEAST_RISKY;
}

AlgorithmCombinationsLeastRisky::~AlgorithmCombinationsLeastRisky() {}

AlgorithmStatus AlgorithmCombinationsLeastRisky::Execution()
{
    const uint32_t safest_field = FindSafestField();
    // Only click if a field was found
    if(safest_field != UINT_MAX)
    {
        QueueAction(safest_field, PlayerAction::LEFT_CLICK);
    }

    return AlgorithmStatus::NO_STATUS;
}

uint32_t AlgorithmCombinationsLeastRisky::FindSafestField() const
{
    const uint32_t face_length = face_dto.face.Index();
    BigNum lowest_combination = max_combinations;
    uint32_t safest_field = UINT_MAX;
    // Find the safest field (index of lowest entry in data.field_combinations)
    for(size_t i = 0; i < face_length; i++)
    {
        const uint32_t face_field = face_dto.face[i];
        const BigNum face_field_combinations = combinations_dto.field_combinations[face_field];
        if(face_field_combinations < lowest_combination)
        {
            lowest_combination = face_field_combinations;
            safest_field = face_field;
        }
    }
    return safest_field;
}
