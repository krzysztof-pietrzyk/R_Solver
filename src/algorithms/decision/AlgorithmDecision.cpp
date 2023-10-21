#include "AlgorithmDecision.hpp"

AlgorithmDecision::AlgorithmDecision(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : Algorithm(grid_, data_),
    grid(grid_),
    visible(grid_.GetVisibleFields()),
    flagged(grid_.GetFlaggedFields()),
    actions_dto(data_.actions_dto)
{
    LOGGER(LogLevel::INIT) << "AlgorithmDecision";
    // Overwrite it in inheriting classes
    algorithm_type = AlgorithmType::UNHANDLED_ALGORITHM_TYPE;
}

AlgorithmDecision::~AlgorithmDecision() {}

AlgorithmStatus AlgorithmDecision::Run()
{
    const size_t count_actions_before = actions_dto.actions.size();
    Execution();
    const size_t count_actions_after = actions_dto.actions.size();
    statistics_executions->executions += 1;
    const size_t count_actions_new = count_actions_after - count_actions_before;
    AlgorithmStatus status;
    if(count_actions_new > 0) { status = AlgorithmStatus::SUCCESS; }
    else                      { status = AlgorithmStatus::NO_MOVES; }
    return status;
}

void AlgorithmDecision::QueueAction(uint32_t field, PlayerAction action)
{
    actions_dto.Add(field, action, algorithm_type);
}
