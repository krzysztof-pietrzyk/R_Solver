#include "SolverThreadData.hpp"

SolverThreadData::SolverThreadData()
{
    LOGGER(LOG_INIT) << "SolverThreadData";
    statistics_data = StatisticsAggregatorStruct();
}

SolverThreadData::~SolverThreadData()
{
    for(auto& item : statistics_data)
    {
        StatisticsProducerStruct producer_data = item.second;
        for(auto& data_pointer : producer_data)
        {
            delete data_pointer;
        }
    }
}
