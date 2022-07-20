#include "AlgorithmAction.hpp"

AlgorithmAction::AlgorithmAction(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_, data_)
{

}

AlgorithmAction::~AlgorithmAction() {}

AlgorithmStatus AlgorithmAction::Run()
{
    metrics.times_activated++;

    #ifdef GATHER_TIME_METRICS
    std::chrono::_V2::system_clock::time_point time_start = std::chrono::high_resolution_clock::now();
    #endif

    AlgorithmStatus action_result = RunInternal();

    #ifdef GATHER_TIME_METRICS
    std::chrono::_V2::system_clock::time_point time_end = std::chrono::high_resolution_clock::now();
    metrics.total_time_running += time_end - time_start;
    #endif

    AlgorithmStatus game_over_result = CheckGameOverConditions();
    if(game_over_result == AlgorithmStatus::NO_STATUS) return action_result;
    else return game_over_result;
}

AlgorithmStatus AlgorithmAction::CheckGameOverConditions()
{
    if(grid.is_lost) return AlgorithmStatus::GAME_LOST;
    else if(grid.visible_fields_index == grid.NM) return AlgorithmStatus::GAME_WON;
    else return AlgorithmStatus::NO_STATUS;
}
