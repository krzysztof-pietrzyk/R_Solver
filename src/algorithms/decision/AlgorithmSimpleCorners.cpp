#include "AlgorithmSimpleCorners.hpp"

AlgorithmSimpleCorners::AlgorithmSimpleCorners(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : AlgorithmDecision(grid_, data_)
{
    LOGGER(LogLevel::INIT) << "AlgorithmSimpleCorners";
    const uint32_t upper_left = 0;
    const uint32_t upper_right = grid_dim.width - 1;
    const uint32_t bottom_left = (grid_dim.height - 1) * grid_dim.width;
    const uint32_t bottom_right = grid_dim.height * grid_dim.width - 1;
    corners = std::vector<uint32_t>();
    corners.push_back(upper_left);
    corners.push_back(upper_right);
    corners.push_back(bottom_left);
    corners.push_back(bottom_right);
    algorithm_type = AlgorithmType::SIMPLE_CORNERS;
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
    if(chosen_corner != UINT32_MAX)
    {
        QueueAction(chosen_corner, PlayerAction::LEFT_CLICK);
    }

    return AlgorithmStatus::NO_STATUS;
}
