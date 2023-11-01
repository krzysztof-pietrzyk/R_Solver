// implemented header
#include "SolverThreadData.hpp"

// project includes
#include "../statistics/StatisticsAggregator.hpp"
#include "../utils/Logger.hpp"

// std includes


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
    LOGGER(LogLevel::INIT) << "SolverThreadData::SetAggregatorIfEmpty";
    if(!statistics_data)
    {
        statistics_data = aggregator->Clone();
    }
}
