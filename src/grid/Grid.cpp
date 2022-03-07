#include "Grid.hpp"

// w - Width, h - Height, m - Number of mines
Grid::Grid(unsigned short int w, unsigned short int h, unsigned int m) : GridManager(w, h, m)
{
    // Mines should be less than Size, at least 1 mine, and Size can't be arbitrarily large
    // It is possible to create a 5000x5000 grid, but it's not recommended to go that big
    if(M >= S || M < 1 || S > (unsigned int)(1e+8)) throw std::invalid_argument("ERROR: Grid constructor parameters are invalid.");

    mines = std::vector<unsigned int>(M, 0);
    not_mines = std::vector<unsigned int>(S - M, 0);
    is_mine = std::vector<bool>(S, false);

    FindNeighbors();
}

Grid::~Grid() {}

void Grid::Clear()
{
    // Only clear the data, which may influence the next generated grid
    for(int i = 0; i < M; i++) is_mine[mines[i]] = false;
    for(int i = 0; i < visible_fields_index; i++) is_visible[visible_fields[i]] = false;
    // Zero the index - old data remains in the array, but will be overwritten before it is used
    visible_fields_index = 0;
    for(int i = 0; i < flags_index; i++) is_flag[flags[i]] = false;
    // Zero the index - old data remains in the array, but will be overwritten before it is used
    flags_index = 0;

    GridManager::Clear();
}

// private
void Grid::FindNeighbors()
{
    // Only called once in constructor. The neighbors addresses never change
    unsigned short int column;
    unsigned short int row;
    for(unsigned int i = 0; i < S; i++)
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
