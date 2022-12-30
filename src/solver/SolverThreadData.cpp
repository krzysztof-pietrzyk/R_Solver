#include "SolverThreadData.hpp"

SolverThreadData::SolverThreadData()
{
    statistics_data = std::map<std::string, std::vector<StatisticsType*>>();
}

SolverThreadData::~SolverThreadData() {}
