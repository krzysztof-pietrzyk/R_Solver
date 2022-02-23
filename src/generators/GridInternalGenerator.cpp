#include "GridInternalGenerator.hpp"

GridInternalGenerator::GridInternalGenerator(GridSelfGenerated& grid_) : GridGenerator(), grid(grid_),
    empty_template(ValueTable(grid.S)), safe_fields(ValueTable(grid.S)), generated_mines(Buffer(grid.M))
{
    for(int i = 0; i < empty_template.Len(); i++) empty_template[i] = i;
}

GridInternalGenerator::~GridInternalGenerator() {}
