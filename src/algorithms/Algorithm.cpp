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
    statistics_executions->executions += 1;
    return execution_result;
}
