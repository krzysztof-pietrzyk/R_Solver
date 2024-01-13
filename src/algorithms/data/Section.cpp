// implemented header
#include "Section.hpp"

// project includes

// std includes
#include <algorithm>


// Section may contain up to 8 fields, like so:
// 00 01 02
// 03 XX 04
// 05 06 07
const uint32_t Section::max_section_length = 8;

// Section may have up to 20 neighbors, like so:
// 00 01 02 03 04
// 05    06    07
// 08 09 XX 10 11
// 12    13    14
// 15 16 17 18 19
const uint32_t Section::max_section_neighbors = 20;

Section::Section()
{
    origin = 0;
    fields = std::vector<uint32_t>(max_section_length, 0);
    fields_index = 0;
    neighbors = std::vector<uint32_t>(max_section_neighbors, 0);
    neighbors_index = 0;
    value = 0;
}

Section::~Section() {}

void Section::AddField(const uint32_t field)
{
    fields[fields_index++] = field;
}

void Section::AddNeighbor(const uint32_t field)
{
    neighbors[neighbors_index++] = field;
}

bool Section::HasNeighbor(const uint32_t field) const
{
    auto end = neighbors.begin() + neighbors_index;
    return std::find(neighbors.begin(), end, field) != end;
}

void Section::Clear()
{
    fields_index = 0;
    neighbors_index = 0;
    value = 0;
}
