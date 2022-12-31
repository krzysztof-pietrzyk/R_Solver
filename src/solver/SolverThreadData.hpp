#ifndef SOLVER_THREAD_DATA_HPP
#define SOLVER_THREAD_DATA_HPP

#include "../statistics/collectors/StatisticsCollector.hpp"

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

    std::map<Label, std::vector<StatisticsCollector*>> statistics_data;
};

#endif
