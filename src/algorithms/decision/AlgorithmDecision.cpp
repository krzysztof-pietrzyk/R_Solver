#include "AlgorithmDecision.hpp"

AlgorithmDecision::AlgorithmDecision(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : Algorithm(grid_, data_),
    grid(grid_),
    actions_dto(data_.actions_dto)
{
    LOGGER(LogLevel::INIT) << "AlgorithmDecision";
    algorithm_type = AlgorithmType::UNHANDLED_ALGORITHM_TYPE;
}

AlgorithmDecision::~AlgorithmDecision() {}

void AlgorithmDecision::QueueAction(uint32_t field, PlayerAction action)
{
    actions_dto.Add(field, action, algorithm_type);
}
