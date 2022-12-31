#include "StatisticsProducer.hpp"

StatisticsProducer::StatisticsProducer()
{
    statistics_types = StatisticsProducerStruct();
}

StatisticsProducer::~StatisticsProducer()
{
    for(auto& type : statistics_types)
    {
        delete type;
    }
}

const StatisticsProducerStruct& StatisticsProducer::GetStatisticsTypes() const
{
    return statistics_types;
}