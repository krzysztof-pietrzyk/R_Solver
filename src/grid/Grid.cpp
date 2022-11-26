#include "Grid.hpp"

// w - Width, h - Height, m - Number of mines
Grid::Grid(uint16_t w, uint16_t h, uint32_t m) : GridManager(w, h, m)
{
    // Mines should be less than Size, at least 1 mine, and Size can't be arbitrarily large
    // It is possible to create a 5000x5000 grid, but it's not recommended to go that big
    if(M >= S || M < 1 || W > 1024 || H > 1024)
    {
        throw std::invalid_argument("ERROR: Grid constructor parameters are invalid.");
    }

    mines = std::vector<uint32_t>(M, 0);
    not_mines = std::vector<uint32_t>(S - M, 0);
    is_mine = std::vector<bool>(S, false);

    FindNeighbors();
}

Grid::~Grid() {}

void Grid::Clear()
{
    // Only clear the data, which may influence the next generated grid
    is_mine.assign(S, false);
    GridManager::Clear();
}

// private
void Grid::FindNeighbors()
{
    // Only called once in constructor. The neighbors addresses never change
    uint16_t column;
    uint16_t row;
    for(uint32_t i = 0; i < S; i++)
    {
        // For each field, list the neighbors
        column = i % W;
        row = i / W;
        if(column - 1 >= 0 && row - 1 >= 0) neighbors[i].push_back(i - 1 - W);  // Upper Left
        if(row - 1 >= 0)                    neighbors[i].push_back(i - W);      // Upper Middle
        if(column + 1 < W && row - 1 >= 0)  neighbors[i].push_back(i + 1 - W);  // Upper Right
        if(column - 1 >= 0)                 neighbors[i].push_back(i - 1);      // Middle Left
        if(column + 1 < W)                  neighbors[i].push_back(i + 1);      // Middle Right
        if(column - 1 >= 0 && row + 1 < H)  neighbors[i].push_back(i - 1 + W);  // Bottom Left
        if(row + 1 < H)                     neighbors[i].push_back(i + W);      // Bottom Middle
        if(column + 1 < W && row + 1 < H)   neighbors[i].push_back(i + 1 + W);  // Bottom Right
    }
}
