#include "SolverThreadData.hpp"

SolverThreadData::SolverThreadData()
{
    statistics_data = std::map<std::string, std::vector<StatisticsType*>>();
}

SolverThreadData::~SolverThreadData()
{
    for(auto& item : statistics_data)
    {
        std::vector<StatisticsType*> producer_data = item.second;
        for(auto& data_pointer : producer_data)
        {
            delete data_pointer;
        }
    }
}
