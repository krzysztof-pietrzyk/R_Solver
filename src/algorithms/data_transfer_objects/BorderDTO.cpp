#include "BorderDTO.hpp"

BorderDTO::BorderDTO(GridDimensions dim)
{
    border = CachedVector(dim.size);
    border_last_visible_fields_index = 0;
}

void BorderDTO::Clear()
{
    border.Clear();
    border_last_visible_fields_index = 0;
}