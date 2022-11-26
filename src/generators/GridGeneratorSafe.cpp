#include "GridGeneratorSafe.hpp"

GridGeneratorSafe::GridGeneratorSafe(GridSelfGenerated& grid) : GridGeneratorUnsafe(grid)
{
    forced_safe = std::vector<uint32_t>(1, 0);
    empty_template = std::vector<uint32_t>(grid.S - 1, 0);
    safe_fields = std::vector<uint32_t>(grid.S - 1, 0);
    SetStartingField(0);
}

GridGeneratorSafe::~GridGeneratorSafe() {}

void GridGeneratorSafe::SetStartingField(uint32_t starting_field)
{
    forced_safe[0] = starting_field;
    uint32_t empty_template_index = 0;
    for(uint32_t i = 0; i < grid.S; i++)
    {
        if(i == starting_field) { continue; }
        empty_template[empty_template_index++] = i;
    }
}

void GridGeneratorSafe::PrepareSafeFields()
{
    const size_t empty_template_size = empty_template.size();
    for(size_t i = 0; i < empty_template_size; i++) safe_fields[i] = empty_template[i];
    current_max = empty_template_size;
}

void GridGeneratorSafe::CopySafeFields()
{
    for(size_t i = 0; i < current_max; i++) grid.not_mines[i] = safe_fields[i];
    safe_fields[current_max] = forced_safe[0];
}