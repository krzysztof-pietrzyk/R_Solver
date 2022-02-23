#include "Grid.hpp"

// w - Width, h - Height, m - Number of mines
Grid::Grid(unsigned short int w, unsigned short int h, unsigned int m) : GridManager(w, h, m),
    mines(Buffer(M)), not_mines(Buffer(S - M)), is_mine(BitMask(S))
{
    FindNeighbors();
}

Grid::~Grid() {}

void Grid::Clear()
{
    // Only clear the data, which may influence the next generated grid
    for(int i = 0; i < M; i++) is_mine[mines[i]] = false;
    mines.Clear();
    not_mines.Clear();

    GridManager::Clear();
}

// private
void Grid::FindNeighbors()
{
    // Only called once in constructor. The neighbors addresses never change
    Buffer neighbors_temp = Buffer(8);
    unsigned short int column;
    unsigned short int row;
    for(unsigned int i = 0; i < S; i++)
    {
        neighbors_temp.Clear();
        // For each field, list the neighbors
        column = i % W;
        row = i / W;
        if(column - 1 >= 0 && row - 1 >= 0) neighbors_temp += i - 1 - W;  // Upper Left
        if(row - 1 >= 0)                    neighbors_temp += i - W;      // Upper Middle
        if(column + 1 < W && row - 1 >= 0)  neighbors_temp += i + 1 - W;  // Upper Right
        if(column - 1 >= 0)                 neighbors_temp += i - 1;      // Middle Left
        if(column + 1 < W)                  neighbors_temp += i + 1;      // Middle Right
        if(column - 1 >= 0 && row + 1 < H)  neighbors_temp += i - 1 + W;  // Bottom Left
        if(row + 1 < H)                     neighbors_temp += i + W;      // Bottom Middle
        if(column + 1 < W && row + 1 < H)   neighbors_temp += i + 1 + W;  // Bottom Right
        if(neighbors_temp.Len() > 0)
        {
            // Store the neighbors in the Buffer
            for(int j = 0; j < neighbors_temp.Len(); j++) neighbors[i] += neighbors_temp[j];
        }
    }
}
