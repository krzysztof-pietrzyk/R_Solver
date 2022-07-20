#include "Algorithm.hpp"

Algorithm::Algorithm(GridManager& grid_, AlgorithmDataStorage& data_) : grid(grid_), data(data_)
{
    metrics = AlgorithmMetrics();
}

Algorithm::~Algorithm() {}

AlgorithmStatus Algorithm::Run()
{
    metrics.times_activated++;
    return RunInternal();
}

void Algorithm::LeftClick(unsigned int field)
{
    metrics.left_clicks++;
    grid.LeftClick(field);
}

void Algorithm::RightClick(unsigned int field)
{
    metrics.right_clicks++;
    grid.RightClick(field);
}
