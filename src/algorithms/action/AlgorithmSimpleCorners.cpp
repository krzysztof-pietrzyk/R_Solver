#include "AlgorithmSimpleCorners.hpp"

AlgorithmSimpleCorners::AlgorithmSimpleCorners(GridManager& grid_, AlgorithmDataStorage& data_) : AlgorithmAction(grid_, data_), 
    corners_number(4)
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

AlgorithmResult AlgorithmSimpleCorners::RunInternal()
{
    for(size_t i = 0; i < corners_number; i++)
    {
        const unsigned int corner = corners[i];
        if(!grid.is_visible[corner] && !grid.is_flag[corner])
        {
            grid.LeftClick(corner);
            return AlgorithmResult::SUCCESS;
        }
    }
    return AlgorithmResult::NO_MOVES;
}
