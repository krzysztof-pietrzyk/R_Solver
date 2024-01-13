// implemented header
#include "BorderDTO.hpp"

// project includes
#include "../../grid/GridDimensions.hpp"

// std includes


BorderDTO::BorderDTO(GridDimensions dim)
{
    border = std::vector<uint32_t>(dim.size, 0);
    is_border = std::vector<bool>(dim.size, false);
    index = 0;
    last_visible_fields_index = 0;
}

void BorderDTO::Clear()
{
    for(size_t i = 0; i < index; ++i)
    {
        uint32_t border_field = border[i];
        is_border[border_field] = false;
    }
    index = 0;
    last_visible_fields_index = 0;
}
