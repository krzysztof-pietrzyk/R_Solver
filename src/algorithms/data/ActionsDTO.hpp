#ifndef ACTION_QUEUE_DTO_HPP
#define ACTION_QUEUE_DTO_HPP

#include "../../grid/GridDimensions.hpp"

#include "../PlayerAction.hpp"
#include "../AlgorithmType.hpp"

#include <map>

struct PlayerActionStruct
{
    PlayerAction action;
    AlgorithmType algorithm_type;
};

struct ActionsDTO
{
    std::map<uint32_t, PlayerActionStruct> actions;

    ActionsDTO(GridDimensions dim);

    void Clear();

    void Add(uint32_t field, PlayerAction new_action, AlgorithmType algorithm_type);
};

#endif
