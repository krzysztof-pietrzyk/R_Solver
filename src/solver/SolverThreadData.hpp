#ifndef SOLVER_THREAD_DATA_HPP
#define SOLVER_THREAD_DATA_HPP

#include "../statistics/StatisticsAggregator.hpp"
#include "../utils/Logger.hpp"

#include <mutex>

class SolverThreadData
{
    public:

    SolverThreadData();

    ~SolverThreadData();

    void SetAggregatorIfEmpty(StatisticsAggregator* aggregator);

	std::mutex mut;

    StatisticsAggregator* statistics_data;
};

#endif
