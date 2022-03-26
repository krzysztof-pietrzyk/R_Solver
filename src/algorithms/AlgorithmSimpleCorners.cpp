#include "AlgorithmSimpleCorners.hpp"

AlgorithmSimpleCorners::AlgorithmSimpleCorners(GridManager& grid_) : Algorithm(grid_), 
    corners_number(4)
{
    unsigned int upper_left = 0;
    unsigned int upper_right = grid.W - 1;
    unsigned int bottom_left = (grid.H - 1) * grid.W;
    unsigned int bottom_right = grid.H * grid.W - 1;
    corners = std::vector<unsigned int>();
    corners.push_back(upper_left);
    corners.push_back(upper_right);
    corners.push_back(bottom_left);
    corners.push_back(bottom_right);
}

AlgorithmSimpleCorners::~AlgorithmSimpleCorners() {}

bool AlgorithmSimpleCorners::Run()
{
    unsigned int corner = 0;
    unsigned int i = 0;
    for(i = 0; i < corners_number; i++)
    {
        corner = corners[i];
        if(!grid.is_visible[corner] && !grid.is_flag[corner])
        {
            grid.LeftClick(corner);
            return true;
        }
    }
    return false;
}
