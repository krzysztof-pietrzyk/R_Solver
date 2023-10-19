#include "GridDimensions.hpp"

GridDimensions::GridDimensions(uint16_t w, uint16_t h, uint32_t m)
{
    width = w;
    height = h;
    mines = m;
    size = w * h;
    safe = size - mines;
}
