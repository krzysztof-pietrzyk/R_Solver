#ifndef GRID_ACCESS_COMMON_IF_HPP
#define GRID_ACCESS_COMMON_IF_HPP

#include "GridDimensions.hpp"

class GridAccessCommonIf
{
    public:

    virtual GridDimensions GetDimensions() const = 0;
    virtual uint16_t GetWidth() const = 0;
    virtual uint16_t GetHeight() const = 0;
    virtual uint32_t GetSize() const = 0;
    virtual uint32_t GetTotalMines() const = 0;
    virtual uint32_t GetTotalSafeFields() const = 0;
    virtual const std::vector<uint32_t>& GetFieldNeighbors(uint32_t field) = 0;
};

#endif
