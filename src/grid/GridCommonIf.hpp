#ifndef GRID_COMMON_IF_HPP
#define GRID_COMMON_IF_HPP

// project includes
#include "GridDimensions.hpp"

// std includes
#include <vector>

// forward declarations
class GridState;


class GridCommonIf
{
    public:

    virtual GridDimensions GetDimensions() const = 0;
    virtual const std::vector<uint32_t>& GetNeighbors(uint32_t field) const = 0;
    virtual GridState GetState() const = 0;
    virtual bool IsLost() const = 0;
    virtual bool IsWon() const = 0;
};

#endif
