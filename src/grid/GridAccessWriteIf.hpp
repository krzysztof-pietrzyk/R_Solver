#ifndef GRID_ACCESS_WRITE_IF_HPP
#define GRID_ACCESS_WRITE_IF_HPP

#include "../utils/CachedVector.hpp"
#include "GridAccessCommonIf.hpp"

#include <vector>
#include <cstdint>

class GridAccessWriteIf : public GridAccessCommonIf
{
    public:

    virtual void SetMinesPositions(const CachedVector& new_mines_positions) = 0;
    virtual void SetFlagsPositions(const CachedVector& new_flags_positions) = 0;
    virtual void SetVisibleFields(const CachedVector& new_visible_fields) = 0;
    virtual void SetFieldValues(const std::vector<uint8_t>& new_field_values) = 0;
};

#endif
