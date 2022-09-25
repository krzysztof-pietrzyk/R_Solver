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

void AlgorithmSimpleCorners::RunInternal()
{
    try
    {
        const unsigned int corner = GetCorner();
        grid.LeftClick(corner);
    }
    catch(const std::exception& e)
    {
        // No corners left
        return;
    }
}

unsigned int AlgorithmSimpleCorners::GetCorner() const
{
    for(const unsigned int corner : corners)
    {
        if(!grid.is_visible[corner] && !grid.is_flag[corner])
        {
            return corner;
        }
    }
    // No corners left
    throw std::exception();
}