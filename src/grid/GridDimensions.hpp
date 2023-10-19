#ifndef GRID_DIMENSIONS_HPP
#define GRID_DIMENSIONS_HPP

#include <cstdint>

struct GridDimensions
{
    uint16_t width;
    uint16_t height;
    uint32_t size;
    uint32_t mines;
    uint32_t safe;

    GridDimensions(uint16_t w, uint16_t h, uint32_t m);
};

#endif
