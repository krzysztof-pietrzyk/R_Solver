#ifndef SOLVER_THREAD_DATA_HPP
#define SOLVER_THREAD_DATA_HPP

// project includes

// std includes
#include <mutex>

// forward declarations
class StatisticsAggregator;
class Logger;


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
