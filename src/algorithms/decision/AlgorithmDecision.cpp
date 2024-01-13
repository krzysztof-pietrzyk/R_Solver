// implemented header
#include "AlgorithmDecision.hpp"

// project includes
#include "../PlayerAction.hpp"
#include "../../statistics/StatisticsCollector.hpp"
#include "../../statistics/StatisticsLabels.hpp"
#include "../../statistics/elements/StatisticsElementCounter.hpp"

// std includes


AlgorithmDecision::AlgorithmDecision(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : Algorithm(grid_, data_),
    grid(grid_),
    visible(grid_.GetVisibleFields()),
    flagged(grid_.GetFlaggedFields()),
    actions_dto(data_.actions_dto)
{
    LOGGER(LogLevel::INIT) << "AlgorithmDecision";
    CreateStatisticsElements();
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
        *decisions_left_click += 1;
    }
    else if(action == PlayerAction::RIGHT_CLICK)
    {
        *decisions_right_click += 1;
    }
}

void AlgorithmDecision::CreateStatisticsElements()
{
    decisions_left_click = new StatisticsElementCounter();
    decisions_right_click = new StatisticsElementCounter();
    statistics_collector->AddElement(Labels::Elements::Decisions::LEFT_CLICKS, decisions_left_click);
    statistics_collector->AddElement(Labels::Elements::Decisions::RIGHT_CLICKS, decisions_right_click);
}
