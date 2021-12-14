#include "AlgorithmSimpleCorners.hpp"

#include <iostream>
using namespace std;

AlgorithmSimpleCorners::AlgorithmSimpleCorners(GridManager& grid_) : Algorithm(grid_), 
    corners_number(4)
{
    unsigned int upper_left = 0;
    unsigned int upper_right = grid.W - 1;
    unsigned int bottom_left = (grid.H - 1) * grid.W;
    unsigned int bottom_right = grid.H * grid.W - 1;
    corners = new unsigned int[corners_number] { upper_left, upper_right, bottom_left, bottom_right };
}

AlgorithmSimpleCorners::~AlgorithmSimpleCorners() {}

bool AlgorithmSimpleCorners::Run()
{
    unsigned int corner = 0;
    for(int i = 0; i < corners_number; i++)
    {
        corner = corners[i];
        if(!grid.is_visible[corner])
        {
            grid.LeftClick(corner);
            return true;
        }
    }
    return false;
}
