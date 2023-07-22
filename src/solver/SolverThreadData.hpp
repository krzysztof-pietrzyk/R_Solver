#ifndef SOLVER_THREAD_DATA_HPP
#define SOLVER_THREAD_DATA_HPP

#include "../statistics/collectors/StatisticsCollector.hpp"
#include "../utils/Logger.hpp"

#include <mutex>
#include <string>
#include <map>
#include <vector>

class SolverThreadData
{
    public:

    SolverThreadData();

    ~SolverThreadData();

	std::mutex mut;

    StatisticsAggregatorStruct statistics_data;
};

#endif
