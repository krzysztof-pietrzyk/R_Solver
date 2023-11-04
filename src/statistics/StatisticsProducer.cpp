// implemented header
#include "StatisticsProducer.hpp"

// project includes
#include "StatisticsCollector.hpp"

// std includes


StatisticsProducer::StatisticsProducer()
{
    statistics_collector = new StatisticsCollector();
}

StatisticsProducer::~StatisticsProducer()
{
    delete statistics_collector;
}

const StatisticsCollector* StatisticsProducer::GetStatisticsCollector()
{
    return statistics_collector;
}
