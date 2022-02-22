#include "Grid.hpp"

// w - Width, h - Height, m - Number of mines
Grid::Grid(unsigned short int w, unsigned short int h, unsigned int m) : GridManager(w, h, m)
{
    mines = new unsigned int[M] {0};
    not_mines = new unsigned int[S - M] {0};
    is_mine = new bool[S] {false};

    neighbors_large = new unsigned int [S * 8] {0};

    FindNeighbors();
}

Grid::~Grid()
{
    delete[] mines;
    delete[] not_mines;
    delete[] is_mine;
    delete[] neighbors_large;
}

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
    unsigned int neighbors_temp[8] {0};
    unsigned char neighbors_count;
    unsigned short int column;
    unsigned short int row;
    for(unsigned int i = 0; i < S; i++)
    {
        // For each field, list the neighbors 
        neighbors_count = 0;
        column = i % W;
        row = i / W;
        if(column - 1 >= 0 && row - 1 >= 0) neighbors_temp[neighbors_count++] = i - 1 - W;  // Upper Left
        if(row - 1 >= 0)                    neighbors_temp[neighbors_count++] = i - W;      // Upper Middle
        if(column + 1 < W && row - 1 >= 0)  neighbors_temp[neighbors_count++] = i + 1 - W;  // Upper Right
        if(column - 1 >= 0)                 neighbors_temp[neighbors_count++] = i - 1;      // Middle Left
        if(column + 1 < W)                  neighbors_temp[neighbors_count++] = i + 1;      // Middle Right
        if(column - 1 >= 0 && row + 1 < H)  neighbors_temp[neighbors_count++] = i - 1 + W;  // Bottom Left
        if(row + 1 < H)                     neighbors_temp[neighbors_count++] = i + W;      // Bottom Middle
        if(column + 1 < W && row + 1 < H)   neighbors_temp[neighbors_count++] = i + 1 + W;  // Bottom Right
        // Store how many neighbors the field has
        neighbors_l[i] = neighbors_count;
        if(neighbors_count > 0)
        {
            // Store the neighbors in the neighbors_large array
            for(int j = 0; j < neighbors_count; j++) neighbors_large[i * 8 + j] = neighbors_temp[j];
            // Store the pointer to that section of neighbors_large array in neighbors array
            neighbors[i] = neighbors_large + i * 8;
        }
    }
}
