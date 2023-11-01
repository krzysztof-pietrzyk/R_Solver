#ifndef BORDER_DTO_HPP
#define BORDER_DTO_HPP

// project includes

// std includes
#include <cstdint>
#include <vector>

// forward declarations
struct GridDimensions;


struct BorderDTO
{
    // CachedVector can't be used here due to optimizations in usage
    std::vector<uint32_t> border;
    std::vector<bool> is_border;
    uint32_t index;
    uint32_t last_visible_fields_index;

    BorderDTO(GridDimensions dim);

    void Clear();
};

#endif
