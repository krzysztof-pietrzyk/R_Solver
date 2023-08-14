#include "AlgorithmSimpleCorners.hpp"

AlgorithmSimpleCorners::AlgorithmSimpleCorners(GridAccessPlayerIf& grid_, AlgorithmDataStorage& data_)
    : AlgorithmDecision(grid_, data_)
{
    LOGGER(LogLevel::INIT) << "AlgorithmSimpleCorners";
    const uint32_t upper_left = 0;
    const uint32_t upper_right = grid.GetWidth() - 1;
    const uint32_t bottom_left = (grid.GetHeight() - 1) * grid.GetWidth();
    const uint32_t bottom_right = grid.GetHeight() * grid.GetWidth() - 1;
    corners = std::vector<uint32_t>();
    corners.push_back(upper_left);
    corners.push_back(upper_right);
    corners.push_back(bottom_left);
    corners.push_back(bottom_right);
}

AlgorithmSimpleCorners::~AlgorithmSimpleCorners() {}

AlgorithmStatus AlgorithmSimpleCorners::Execution()
{
    uint32_t chosen_corner = UINT32_MAX;
    for(const uint32_t corner : corners)
    {
        if(!visible.Contains(corner) && !flagged.Contains(corner))
        {
            chosen_corner = corner;
            break;
        }
    }
    if(chosen_corner != UINT32_MAX) { LeftClick(chosen_corner); }

    return AlgorithmStatus::NO_STATUS;
}
