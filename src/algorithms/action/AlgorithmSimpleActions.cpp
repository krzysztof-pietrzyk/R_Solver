#include "AlgorithmSimpleActions.hpp"

AlgorithmSimpleActions::AlgorithmSimpleActions(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : AlgorithmAction(grid_, data_),
    actions_dto(data_.actions_dto)
{

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
            LeftClick(field);
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
