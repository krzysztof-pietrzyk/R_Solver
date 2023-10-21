#include "AlgorithmSimpleActions.hpp"

AlgorithmSimpleActions::AlgorithmSimpleActions(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : AlgorithmAction(grid_, data_),
    actions_dto(data_.actions_dto)
{
    LOGGER(LogLevel::INIT) << "AlgorithmSimpleActions";
    statistics_loss = new StatisticsCollectorActionsLoss();  // deleted in StatisticsProducer
    statistics_collectors.push_back(statistics_loss);
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

void AlgorithmSimpleActions::UpdateLossStatistics(AlgorithmType algorithm_type)
{
    switch(algorithm_type)
    {
        case AlgorithmType::SIMPLE_CORNERS:
            statistics_loss->loss_simple_corners += 1;
            break;
        case AlgorithmType::COMBINATIONS_LEAST_RISKY:
            statistics_loss->loss_combinations_least_risky += 1;
            break;
        default:
            statistics_loss->loss_other += 1;
            break;
    }
}
