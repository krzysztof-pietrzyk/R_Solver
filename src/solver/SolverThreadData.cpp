#include "SolverThreadData.hpp"

SolverThreadData::SolverThreadData()
{
    LOGGER(LOG_INIT) << "SolverThreadData";
    statistics_data = std::map<Label, std::vector<StatisticsCollector*>>();
}

SolverThreadData::~SolverThreadData()
{
    for(auto& item : statistics_data)
    {
        std::vector<StatisticsCollector*> producer_data = item.second;
        for(auto& data_pointer : producer_data)
        {
            delete data_pointer;
        }
    }
}
