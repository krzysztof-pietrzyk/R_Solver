#include "GridInternalGenerator.hpp"

GridInternalGenerator::GridInternalGenerator(GridSelfGenerated& grid_) : GridGenerator(), grid(grid_)
{
    empty_template = std::vector<unsigned int>(grid.S, 0);
    for(unsigned int i = 0; i < grid.S; i++) empty_template[i] = i;

    safe_fields = std::vector<unsigned int>(grid.S, 0);
    safe_fields_index = grid.S;

    generated_mines = std::vector<unsigned int>(grid.M, 0);
    generated_mines_index = 0;   
}

GridInternalGenerator::~GridInternalGenerator() {}