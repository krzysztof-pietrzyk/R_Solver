#ifndef STATISTICS_AGGREGATOR_HPP
#define STATISTICS_AGGREGATOR_HPP

#include "collectors/StatisticsCollector.hpp"
#include "StatisticsProducer.hpp"

#include <map>
#include <vector>
#include <string>

class StatisticsAggregator
{
    public:

    StatisticsAggregator();

    ~StatisticsAggregator();

    void RegisterStatisticsProducer(const Label producer_label, const StatisticsProducer* statistics_producer);

    void FlushCurrentDataToOutput(StatisticsAggregatorStruct& output) const;

    protected:

    StatisticsAggregatorStruct aggregated_statistics;
};

#endif
