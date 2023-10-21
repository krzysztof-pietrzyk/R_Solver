#include "SegmentsDTO.hpp"

SegmentsDTO::SegmentsDTO(GridDimensions dim)
{
    segments_index = 0;
    segments_count = 0;
    segments = std::vector<uint32_t>(dim.safe, 0);
    segments_starting_indexes = std::vector<uint32_t>(dim.safe, 0);
    segments_l = std::vector<uint32_t>(dim.safe, 0);
}

void SegmentsDTO::Clear()
{
    segments_index = 0;
    segments_count = 0;
}

void SegmentsDTO::AddField(uint32_t field)
{
    segments[segments_index++] = field;
}

void SegmentsDTO::AddSegment(uint32_t start, uint32_t length)
{
    segments_starting_indexes[segments_count] = start;
    segments_l[segments_count] = length;
    segments_count++;
}