#ifndef SEGMENTS_DTO_HPP
#define SEGMENTS_DTO_HPP

// project includes

// std includes
#include <cstdint>
#include <vector>

// forward declarations
struct GridDimensions;


struct SegmentsDTO
{
    uint32_t segments_index;
    uint32_t segments_count;
    std::vector<uint32_t> segments;
    std::vector<uint32_t> segments_starting_indexes;
    std::vector<uint32_t> segments_l;

    SegmentsDTO(GridDimensions dim);

    void Clear();

    void AddField(uint32_t field);

    void AddSegment(uint32_t start, uint32_t length);
};

#endif
