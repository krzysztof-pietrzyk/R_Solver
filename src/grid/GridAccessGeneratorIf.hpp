#ifndef GRID_ACCESS_GENERATOR_IF_HPP
#define GRID_ACCESS_GENERATOR_IF_HPP

#include "../utils/CachedVector.hpp"
#include "GridAccessCommonIf.hpp"

#include <vector>
#include <cstdint>

class GridAccessGeneratorIf : public GridAccessCommonIf
{
    public:

    virtual void SetMineFields(const CachedVector& new_mine_fields) = 0;
    virtual void SetFlaggedFields(const CachedVector& new_flagged_fields) = 0;
    virtual void SetVisibleFields(const CachedVector& new_visible_fields) = 0;
    virtual void SetFieldValues(const std::vector<uint8_t>& new_field_values) = 0;
    virtual void ClearFlaggedFields() = 0;
    virtual void ClearVisibleFields() = 0;
};

#endif
