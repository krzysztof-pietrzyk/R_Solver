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
    GridManager::Clear();
}

// private
void Grid::FindNeighbors()
{
    // Only called once in constructor. The neighbors addresses never change
    unsigned short int column;
    unsigned short int row;
    unsigned int offset = 0;
    unsigned char neighbors_count = 0;
    for(unsigned int i = 0; i < S; i++)
    {
        // For each field, list the neighbors
        column = i % W;
        row = i / W;
        offset = i * MAX_NEIGHBORS;
        neighbors_count = 0;
        if(column - 1 >= 0 && row - 1 >= 0) neighbors[offset + neighbors_count++] = i - 1 - W;  // Upper Left
        if(row - 1 >= 0)                    neighbors[offset + neighbors_count++] = i - W;      // Upper Middle
        if(column + 1 < W && row - 1 >= 0)  neighbors[offset + neighbors_count++] = i + 1 - W;  // Upper Right
        if(column - 1 >= 0)                 neighbors[offset + neighbors_count++] = i - 1;      // Middle Left
        if(column + 1 < W)                  neighbors[offset + neighbors_count++] = i + 1;      // Middle Right
        if(column - 1 >= 0 && row + 1 < H)  neighbors[offset + neighbors_count++] = i - 1 + W;  // Bottom Left
        if(row + 1 < H)                     neighbors[offset + neighbors_count++] = i + W;      // Bottom Middle
        if(column + 1 < W && row + 1 < H)   neighbors[offset + neighbors_count++] = i + 1 + W;  // Bottom Right

        neighbors_l[i] = neighbors_count;
    }
}
