#include "Algorithm.hpp"

Algorithm::Algorithm(GridAccessPlayerIf& grid_, AlgorithmDataStorage& data_)
    : grid(grid_), data(data_), _grid(grid_), _data(data_), 
    visible(grid_.GetVisibleFields()), flagged(grid_.GetFlaggedFields())
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

AlgorithmDataStorage& Algorithm::GetModifiableAlgorithmDataStorageReference() const
{
    return _data;
}
