#include "Section.hpp"

Section::Section()
{
    origin = 0;
    fields = std::vector<uint32_t>(MAX_SECTION_LEN, 0);
    fields_index = 0;
    neighbors = std::vector<uint32_t>(MAX_SECTION_NEIGHBORS, 0);
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