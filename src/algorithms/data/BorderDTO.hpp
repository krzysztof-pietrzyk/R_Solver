#ifndef BORDER_DTO_HPP
#define BORDER_DTO_HPP

#include <vector>
#include <cstdint>

#include "../../grid/GridDimensions.hpp"
#include "../../utils/CachedVector.hpp"

struct BorderDTO
{
    CachedVector border;
    uint32_t border_last_visible_fields_index;

    BorderDTO(GridDimensions dim);

    void Clear();
};

#endif
