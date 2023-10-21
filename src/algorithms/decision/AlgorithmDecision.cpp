#include "AlgorithmDecision.hpp"

AlgorithmDecision::AlgorithmDecision(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : Algorithm(grid_, data_),
    grid(grid_),
    visible(grid_.GetVisibleFields()),
    flagged(grid_.GetFlaggedFields()),
    actions_dto(data_.actions_dto)
{
    LOGGER(LogLevel::INIT) << "AlgorithmDecision";
    statistics_decisions = new StatisticsCollectorDecisions();  // deleted in StatisticsProducer
    statistics_collectors.push_back(statistics_decisions);
    // Overwrite it in inheriting classes
    algorithm_type = AlgorithmType::UNHANDLED_ALGORITHM_TYPE;
}

AlgorithmDecision::~AlgorithmDecision() {}

AlgorithmStatus AlgorithmDecision::Run()
{
    const size_t count_actions_before = actions_dto.actions.size();
    Execution();
    const size_t count_actions_after = actions_dto.actions.size();
    const size_t count_actions_new = count_actions_after - count_actions_before;
    AlgorithmStatus status;
    if(count_actions_new > 0) { status = AlgorithmStatus::SUCCESS; }
    else                      { status = AlgorithmStatus::NO_MOVES; }
    UpdateExecutionStatistics(status);
    return status;
}

void AlgorithmDecision::QueueAction(uint32_t field, PlayerAction action)
{
    actions_dto.Add(field, action, algorithm_type);
    if(action == PlayerAction::LEFT_CLICK)
    {
        statistics_decisions->decisions_left_click += 1;
    }
    else if(action == PlayerAction::RIGHT_CLICK)
    {
        statistics_decisions->decisions_right_click += 1;
    }
}
