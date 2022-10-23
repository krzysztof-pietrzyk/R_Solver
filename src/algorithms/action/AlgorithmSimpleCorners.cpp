#include "AlgorithmSimpleCorners.hpp"

AlgorithmSimpleCorners::AlgorithmSimpleCorners(GridManager& grid_, AlgorithmDataStorage& data_)
    : AlgorithmAction(grid_, data_),
    is_flag(grid.is_flag), is_visible(grid.is_visible)
{
    const unsigned int upper_left = 0;
    const unsigned int upper_right = grid.W - 1;
    const unsigned int bottom_left = (grid.H - 1) * grid.W;
    const unsigned int bottom_right = grid.H * grid.W - 1;
    corners = std::vector<unsigned int>();
    corners.push_back(upper_left);
    corners.push_back(upper_right);
    corners.push_back(bottom_left);
    corners.push_back(bottom_right);
}

AlgorithmSimpleCorners::~AlgorithmSimpleCorners() {}

void AlgorithmSimpleCorners::RunInternal()
{
    unsigned int chosen_corner = UINT32_MAX;
    for(const unsigned int corner : corners)
    {
        if(!is_visible[corner] && !is_flag[corner])
        {
            chosen_corner = corner;
            break;
        }
    }
    if(chosen_corner != UINT32_MAX) grid.LeftClick(chosen_corner);
}
