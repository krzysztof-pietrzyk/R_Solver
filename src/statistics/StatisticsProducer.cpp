#include "StatisticsProducer.hpp"

StatisticsProducer::StatisticsProducer()
{
    statistics_types = std::vector<StatisticsType*>();
}

StatisticsProducer::~StatisticsProducer()
{

}

const std::vector<StatisticsType*>& StatisticsProducer::GetStatisticsTypes() const
{
    return statistics_types;
}