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
