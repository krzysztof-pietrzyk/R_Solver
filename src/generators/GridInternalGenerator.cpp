#include "GridInternalGenerator.hpp"

GridInternalGenerator::GridInternalGenerator(GridSelfGenerated& grid_) : GridGenerator(), grid(grid_)
{
    empty_template = std::vector<uint32_t>(grid.S, 0);
    for(uint32_t i = 0; i < grid.S; i++) empty_template[i] = i;

    safe_fields = std::vector<uint32_t>(grid.S, 0);
    safe_fields_index = grid.S;

    generated_mines = std::vector<uint32_t>(grid.M, 0);
    generated_mines_index = 0;   
}

GridInternalGenerator::~GridInternalGenerator() {}