#include "Algorithm.hpp"

Algorithm::Algorithm(const GridCommonIf& grid_, AlgorithmDataTransfer& data_)
    : data(data_),
    grid_dim(grid_.GetDimensions())
{
    LOGGER(LogLevel::INIT) << "Algorithm";
    CreateStatisticsElements();
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

void Algorithm::CreateStatisticsElements()
{
    counter_executions = new StatisticsElementCounter();
    counter_success = new StatisticsElementCounter();
    counter_no_moves = new StatisticsElementCounter();
    counter_failure = new StatisticsElementCounter();
    counter_won = new StatisticsElementCounter();
    counter_lost = new StatisticsElementCounter();
    statistics_collector->AddElement(Labels::Collectors::Executions::EXECUTIONS, counter_executions);
    statistics_collector->AddElement(Labels::Collectors::Executions::SUCCESS, counter_success);
    statistics_collector->AddElement(Labels::Collectors::Executions::NO_MOVES, counter_no_moves);
    statistics_collector->AddElement(Labels::Collectors::Executions::FAILURE, counter_failure);
    statistics_collector->AddElement(Labels::Collectors::Executions::GAME_WON, counter_won);
    statistics_collector->AddElement(Labels::Collectors::Executions::GAME_LOST, counter_lost);
}

void Algorithm::UpdateExecutionStatistics(AlgorithmStatus status)
{
    *counter_executions += 1;
    switch(status)
    {
        case AlgorithmStatus::SUCCESS:
            *counter_success += 1;
            break;
        case AlgorithmStatus::NO_MOVES:
            *counter_no_moves += 1;
            break;
        case AlgorithmStatus::GAME_WON:
            *counter_won += 1;
            break;
        case AlgorithmStatus::GAME_LOST:
            *counter_lost += 1;
            break;
        case AlgorithmStatus::FAILURE:
            *counter_failure += 1;
            break;
        default:
            break;
    }
}
