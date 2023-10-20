#include "ActionsDTO.hpp"

ActionsDTO::ActionsDTO(GridDimensions dim)
{
    actions = std::map<uint32_t, PlayerActionStruct>();
}

void ActionsDTO::Clear()
{
    actions.clear();
}

void ActionsDTO::Add(uint32_t field, PlayerAction new_action, AlgorithmType algorithm_type)
{
    PlayerActionStruct action_struct = PlayerActionStruct();
    action_struct.action = new_action;
    action_struct.algorithm_type = algorithm_type;
    actions[field] = action_struct;
}
