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

    GridDimensions(uint16_t w, uint16_t h, uint32_t m)
    {
        width = w;
        height = h;
        mines = m;
        size = w * h;
        safe = size - mines;
    }
};

const GridDimensions GRID_DIMENSIONS_BEGINNER = GridDimensions(9U, 9U, 10U);
const GridDimensions GRID_DIMENSIONS_INTERMEDIATE = GridDimensions(16U, 16U, 40U);
const GridDimensions GRID_DIMENSIONS_EXPERT = GridDimensions(30U, 16U, 99U);

#endif
