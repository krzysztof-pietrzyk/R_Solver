#ifndef ACTION_QUEUE_DTO_HPP
#define ACTION_QUEUE_DTO_HPP

// project includes

// std includes
#include <cstdint>
#include <map>

// forward declarations
struct PlayerActionStruct;
struct GridDimensions;
enum class PlayerAction;
enum class AlgorithmType;


struct ActionsDTO
{
    std::map<uint32_t, PlayerActionStruct> actions;

    ActionsDTO(GridDimensions dim);

    void Clear();

    void Add(uint32_t field, PlayerAction new_action, AlgorithmType algorithm_type);
};

#endif
