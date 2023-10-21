#include "Algorithm.hpp"

Algorithm::Algorithm(const GridCommonIf& grid_, AlgorithmDataTransfer& data_)
    : data(data_),
    grid_dim(grid_.GetDimensions())
{
    LOGGER(LogLevel::INIT) << "Algorithm";
    statistics_executions = new StatisticsCollectorExecutions();  // deleted in StatisticsProducer
    statistics_collectors.push_back(statistics_executions);
}

Algorithm::~Algorithm()
{

}

AlgorithmStatus Algorithm::Run()
{
    AlgorithmStatus execution_result = Execution();
    UpdateExecutionStatistics(execution_result);
    return execution_result;
}

void Algorithm::UpdateExecutionStatistics(AlgorithmStatus status)
{
    statistics_executions->executions += 1;
    switch(status)
    {
        case AlgorithmStatus::SUCCESS:
            statistics_executions->success += 1;
            break;
        case AlgorithmStatus::NO_MOVES:
            statistics_executions->no_moves += 1;
            break;
        case AlgorithmStatus::GAME_WON:
            statistics_executions->game_won += 1;
            break;
        case AlgorithmStatus::GAME_LOST:
            statistics_executions->game_lost += 1;
            break;
        case AlgorithmStatus::FAILURE:
            statistics_executions->failure += 1;
            break;
        default:
            break;
    }
}
