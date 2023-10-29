#ifndef STATISTICS_AGGREGATOR_HPP
#define STATISTICS_AGGREGATOR_HPP

#include "../utils/Logger.hpp"

#include "StatisticsProducer.hpp"

class StatisticsAggregator
{
    public:

    StatisticsAggregator();

    ~StatisticsAggregator();

    void RegisterStatisticsProducer(const Label producer_label, StatisticsProducer* statistics_producer);

    StatisticsAggregator* Clone() const;

    std::string String() const;

    void FlushToOutput(StatisticsAggregator* output) const;

    protected:

    std::map<Label, StatisticsProducer*> labelled_producers;
};

#endif
