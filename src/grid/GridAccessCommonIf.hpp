#ifndef GRID_ACCESS_COMMON_IF_HPP
#define GRID_ACCESS_COMMON_IF_HPP

#include "../utils/Logger.hpp"

#include "GridHash.hpp"
#include "GridDimensions.hpp"

class GridAccessCommonIf
{
    public:

    virtual GridDimensions GetDimensions() const = 0;
    virtual const std::vector<uint32_t>& GetNeighbors(uint32_t field) const = 0;
    virtual GridHash GetHash() const = 0;
};

#endif
