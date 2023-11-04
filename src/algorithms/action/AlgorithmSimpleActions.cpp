// implemented header
#include "AlgorithmSimpleActions.hpp"

// project includes
#include "../AlgorithmType.hpp"
#include "../PlayerAction.hpp"
#include "../data/PlayerActionStruct.hpp"
#include "../../statistics/StatisticsCollector.hpp"
#include "../../statistics/StatisticsLabels.hpp"
#include "../../statistics/elements/StatisticsElementCounter.hpp"

// std includes


AlgorithmSimpleActions::AlgorithmSimpleActions(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : AlgorithmAction(grid_, data_),
    actions_dto(data_.actions_dto)
{
    LOGGER(LogLevel::INIT) << "AlgorithmSimpleActions";
    CreateStatisticsElements();
}

AlgorithmSimpleActions::~AlgorithmSimpleActions()
{

}

AlgorithmStatus AlgorithmSimpleActions::Execution()
{
    for(auto& action_tuple : actions_dto.actions)
    {
        uint32_t field = action_tuple.first;
        PlayerAction action = action_tuple.second.action;
        AlgorithmType algorithm_type = action_tuple.second.algorithm_type;

        if(action == PlayerAction::LEFT_CLICK)
        {
            const bool is_lost_before = grid.IsLost();
            LeftClick(field);
            const bool is_lost_after = grid.IsLost();
            const bool caused_loss = is_lost_before != is_lost_after;
            if(caused_loss)
            {
                UpdateLossStatistics(algorithm_type);
                break;
            }
        }
        else if(action == PlayerAction::RIGHT_CLICK)
        {
            RightClick(field);
        }
        else
        {
            LOGGER_THROW("AlgorithmSimpleActions::Execution() - Unhandled PlayerAction");
        }
    }
    actions_dto.Clear();

    return AlgorithmStatus::NO_STATUS;
}

void AlgorithmSimpleActions::CreateStatisticsElements()
{
    counter_loss_simple_corners = new StatisticsElementCounter();
    counter_loss_combinations_least_risky = new StatisticsElementCounter();
    counter_loss_other = new StatisticsElementCounter();
    statistics_collector->AddElement(Labels::Elements::ActionsLoss::SIMPLE_CORNERS, counter_loss_simple_corners);
    statistics_collector->AddElement(Labels::Elements::ActionsLoss::LEAST_RISKY, counter_loss_combinations_least_risky);
    statistics_collector->AddElement(Labels::Elements::ActionsLoss::OTHER, counter_loss_other);
}

void AlgorithmSimpleActions::UpdateLossStatistics(AlgorithmType algorithm_type)
{
    switch(algorithm_type)
    {
        case AlgorithmType::SIMPLE_CORNERS:
            *counter_loss_simple_corners += 1;
            break;
        case AlgorithmType::COMBINATIONS_LEAST_RISKY:
            *counter_loss_combinations_least_risky += 1;
            break;
        default:
            *counter_loss_other += 1;
            break;
    }
}
