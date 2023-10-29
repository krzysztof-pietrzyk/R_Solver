#include "SolverThreadData.hpp"

SolverThreadData::SolverThreadData()
{
    LOGGER(LogLevel::INIT) << "SolverThreadData";
    statistics_data = nullptr;
}

SolverThreadData::~SolverThreadData()
{
    if(statistics_data)
    {
        delete statistics_data;
    }
}

void SolverThreadData::SetAggregatorIfEmpty(StatisticsAggregator* aggregator)
{
    if(!statistics_data)
    {
        statistics_data = aggregator->Clone();
    }
}