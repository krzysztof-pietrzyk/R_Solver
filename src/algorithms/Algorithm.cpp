#include "Algorithm.hpp"

Algorithm::Algorithm(GridManager& grid_, AlgorithmDataStorage& data_)
    : grid(grid_), data(data_), _grid(grid_), _data(data_)
{
    statistics_executions = new StatisticsCollectorExecutions();  // deleted in StatisticsProducer
    statistics_collectors.push_back(statistics_executions);
}

Algorithm::~Algorithm()
{

}

AlgorithmStatus Algorithm::Run()
{
    statistics_executions->executions += 1;
    AlgorithmStatus execution_result = Execution();
    return execution_result;
}

AlgorithmStatus Algorithm::Setup() { return AlgorithmStatus::NO_STATUS; }
AlgorithmStatus Algorithm::Teardown() { return AlgorithmStatus::NO_STATUS; }

bool Algorithm::LeftClick(const uint32_t field) const
{
    return _grid.LeftClick(field);
}

bool Algorithm::RightClick(const uint32_t field) const
{
    return _grid.RightClick(field);
}

uint8_t Algorithm::FieldValue(const uint32_t field) const
{
    return _grid.FieldValue(field);
}

GridManager& Algorithm::GetModifiableGridManagerReference() const
{
    return _grid;
}

AlgorithmDataStorage& Algorithm::GetModifiableAlgorithmDataStorageReference() const
{
    return _data;
}
