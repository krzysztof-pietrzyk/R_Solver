#ifndef SOLVER_THREAD_DATA_HPP
#define SOLVER_THREAD_DATA_HPP

#include "../statistics/types/StatisticsType.hpp"

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

    std::map<std::string, std::vector<StatisticsType*>> statistics_data;
};

#endif
