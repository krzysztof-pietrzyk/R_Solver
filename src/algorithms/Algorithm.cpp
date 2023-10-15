#include "Algorithm.hpp"

Algorithm::Algorithm(GridAccessPlayerIf& grid_, AlgorithmDataTransfer& data_)
    : grid(grid_), data(data_), _grid(grid_), _data(data_), 
    visible(grid_.GetVisibleFields()), flagged(grid_.GetFlaggedFields()), grid_dim(grid_.GetDimensions())
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
    statistics_executions->executions += 1;
    return execution_result;
}

GridAccessPlayerIf& Algorithm::GetModifiableGridReference() const
{
    return _grid;
}

AlgorithmDataTransfer& Algorithm::GetModifiableAlgorithmDataTransferReference() const
{
    return _data;
}
