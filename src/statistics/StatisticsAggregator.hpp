#ifndef STATISTICS_AGGREGATOR_HPP
#define STATISTICS_AGGREGATOR_HPP

#include "../utils/Logger.hpp"

#include "collectors/StatisticsCollector.hpp"
#include "StatisticsProducer.hpp"

class StatisticsAggregator
{
    public:

    StatisticsAggregator();

    ~StatisticsAggregator();

    void RegisterStatisticsProducer(const Label producer_label, const StatisticsProducer* statistics_producer);

    void FlushToOutput(StatisticsAggregatorStruct& output) const;

    protected:

    StatisticsAggregatorStruct aggregated_statistics;
};

#endif
