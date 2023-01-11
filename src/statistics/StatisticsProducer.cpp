#include "StatisticsProducer.hpp"

StatisticsProducer::StatisticsProducer()
{
    statistics_collectors = StatisticsProducerStruct();
}

StatisticsProducer::~StatisticsProducer()
{
    for(auto& type : statistics_collectors)
    {
        delete type;
    }
}

const StatisticsProducerStruct& StatisticsProducer::GetStatisticsCollectors() const
{
    return statistics_collectors;
}
