#ifndef GRID_ALGORITHM_ACTION_IF_HPP
#define GRID_ALGORITHM_ACTION_IF_HPP

#include "../utils/CachedVector.hpp"

#include "GridCommonIf.hpp"

enum class PlayerActionResult
{
    CORRECT,
    EXPLODED,
    WASTED
};

class GridAlgorithmActionIf : public GridCommonIf
{
    public:

    virtual PlayerActionResult SetVisible(uint32_t field) = 0;
    virtual PlayerActionResult SetFlag(uint32_t field) = 0;
    virtual void GiveUp() = 0;
};

#endif
