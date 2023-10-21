#ifndef GRID_GENERATOR_IF_HPP
#define GRID_GENERATOR_IF_HPP

#include "../utils/CachedVector.hpp"

#include "GridCommonIf.hpp"

#include <vector>
#include <cstdint>

class GridGeneratorIf : public GridCommonIf
{
    public:

    virtual void SetMineFields(const CachedVector& new_mine_fields) = 0;
    virtual void SetFlaggedFields(const CachedVector& new_flagged_fields) = 0;
    virtual void SetVisibleFields(const CachedVector& new_visible_fields) = 0;
    virtual void SetFieldValues(const std::vector<uint8_t>& new_field_values) = 0;
    virtual void Reset() = 0;
};

#endif
