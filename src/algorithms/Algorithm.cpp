#include "Algorithm.hpp"

Algorithm::Algorithm(GridManager& grid_, AlgorithmDataStorage& data_) : grid(grid_), data(data_)
{
    metrics = AlgorithmMetrics();
}

Algorithm::~Algorithm() {}

AlgorithmStatus Algorithm::Run()
{
    metrics.times_activated++;

    #ifdef GATHER_TIME_METRICS
    std::chrono::_V2::system_clock::time_point time_start = std::chrono::high_resolution_clock::now();
    #endif

    AlgorithmStatus result = RunInternal();

    #ifdef GATHER_TIME_METRICS
    std::chrono::_V2::system_clock::time_point time_end = std::chrono::high_resolution_clock::now();
    metrics.total_time_running += time_end - time_start;
    #endif

    return result;
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
