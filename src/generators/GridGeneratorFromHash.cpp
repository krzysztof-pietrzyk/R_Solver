#include "GridGeneratorFromHash.hpp"

GridGeneratorFromHash::GridGeneratorFromHash(GridSelfGenerated& grid)
    : GridInternalGenerator(grid), hash(GridHash(grid.S))
{

}

GridGeneratorFromHash::~GridGeneratorFromHash()
{

}

void GridGeneratorFromHash::Generate()
{
    hash = std::string("4P8S@B4D0008P3TPH3b0`6D550P1P0081Z0b0240DU4010008P489`284QbPX4@8Q7@6810808T80D>2");
    grid.Clear();
    hash.GetMines(grid.is_mine);
    grid.hash = hash;
    size_t mines_index = 0;
    size_t not_mines_index = 0; 
    for(size_t i = 0; i < grid.S; i++)
    {
        if(grid.is_mine[i])
        {
            if(mines_index == grid.M)
            {
                throw std::invalid_argument("Error: GridGeneratorFromHash: Too many mines in hash!");
            }
            grid.mines[mines_index++] = i;
        }
        else
        {
            if(not_mines_index == grid.NM)
            {
                throw std::invalid_argument("Error: GridGeneratorFromHash: Too few mines in hash!");
            }
            grid.not_mines[not_mines_index++] = i;
        }
    }
    grid.CalculateValues();
}
