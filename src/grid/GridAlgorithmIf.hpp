#ifndef GRID_ALGORITHM_IF_HPP
#define GRID_ALGORITHM_IF_HPP

// project includes
#include "GridCommonIf.hpp"
#include "../algorithms/PlayerActionResult.hpp"

// std includes

// forward declarations
class CachedVector;


class GridAlgorithmIf : public GridCommonIf
{
    public:

    virtual const CachedVector& GetVisibleFields() const = 0;
    virtual const CachedVector& GetFlaggedFields() const = 0;
    virtual uint8_t GetFieldValue(uint32_t field) const = 0;

    virtual PlayerActionResult SetVisible(uint32_t field) = 0;
    virtual PlayerActionResult SetFlag(uint32_t field) = 0;
    virtual void GiveUp() = 0;
};

#endif
