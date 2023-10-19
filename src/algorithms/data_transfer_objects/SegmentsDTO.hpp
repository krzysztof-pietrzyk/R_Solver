#ifndef SEGMENTS_DTO_HPP
#define SEGMENTS_DTO_HPP

#include <vector>
#include <cstdint>

#include "../../grid/GridDimensions.hpp"

struct SegmentsDTO
{
    uint32_t segments_index;
    uint32_t segments_count;
    std::vector<uint32_t> segments;
    std::vector<uint32_t> segments_starting_indexes;
    std::vector<uint32_t> segments_l;

    SegmentsDTO(GridDimensions dim);

    void Clear();
};

#endif
