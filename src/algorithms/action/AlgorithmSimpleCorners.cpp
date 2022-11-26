#include "AlgorithmSimpleCorners.hpp"

AlgorithmSimpleCorners::AlgorithmSimpleCorners(GridManager& grid_, AlgorithmDataStorage& data_)
    : AlgorithmAction(grid_, data_)
{
    const uint32_t upper_left = 0;
    const uint32_t upper_right = grid.W - 1;
    const uint32_t bottom_left = (grid.H - 1) * grid.W;
    const uint32_t bottom_right = grid.H * grid.W - 1;
    corners = std::vector<uint32_t>();
    corners.push_back(upper_left);
    corners.push_back(upper_right);
    corners.push_back(bottom_left);
    corners.push_back(bottom_right);
}

AlgorithmSimpleCorners::~AlgorithmSimpleCorners() {}

void AlgorithmSimpleCorners::RunInternal()
{
    uint32_t chosen_corner = UINT32_MAX;
    for(const uint32_t corner : corners)
    {
        if(!grid.is_visible[corner] && !grid.is_flag[corner])
        {
            chosen_corner = corner;
            break;
        }
    }
    if(chosen_corner != UINT32_MAX) LeftClick(chosen_corner);
}
