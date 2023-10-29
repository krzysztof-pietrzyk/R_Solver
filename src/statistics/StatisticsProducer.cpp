#include "StatisticsProducer.hpp"

StatisticsProducer::StatisticsProducer()
{
    statistics_collector = new StatisticsCollector();
}

StatisticsProducer::~StatisticsProducer()
{
    delete statistics_collector;
}

StatisticsProducer* StatisticsProducer::Clone() const
{
    StatisticsProducer* cloned_producer = new StatisticsProducer();
    delete cloned_producer->statistics_collector;
    cloned_producer->statistics_collector = statistics_collector->Clone();
    return cloned_producer;
}

std::string StatisticsProducer::String() const
{
    return statistics_collector->String();
}

void StatisticsProducer::FlushToOutput(StatisticsProducer* output) const
{
    statistics_collector->FlushToOutput(output->statistics_collector);
}
