#include "GridGenerator.hpp"

GridGenerator::GridGenerator(Grid& grid) : grid(grid)
{
    empty_template = new unsigned int[grid.S] {0};
    for(int i = 0; i < grid.S; i++) empty_template[i] = i;

    safe_fields = new unsigned int[grid.S] {0};
    safe_fields_index = grid.S;

    generated_mines = new unsigned int[grid.M] {0};
    generated_mines_index = 0;   
}

GridGenerator::~GridGenerator()
{
    delete[] empty_template;
    delete[] safe_fields;
    delete[] generated_mines;
}