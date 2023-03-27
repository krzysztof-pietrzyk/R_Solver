#ifndef GRID_ACCESS_READ_IF_HPP
#define GRID_ACCESS_READ_IF_HPP

#include "../utils/CachedVector.hpp"
#include "GridAccessCommonIf.hpp"

#include <vector>
#include <cstdint>

class GridAccessReadIf : public GridAccessCommonIf
{
    public:

    virtual const CachedVector& GetVisibleFields() const = 0;
    virtual const CachedVector& GetFlagsPositions() const = 0;
    virtual const std::vector<uint32_t>& GetFieldNeighbors(uint32_t field) = 0;
    virtual uint8_t GetFieldValue(uint32_t field) = 0;
};

#endif
