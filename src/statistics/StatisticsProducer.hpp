#ifndef STATISTICS_PRODUCER_HPP
#define STATISTICS_PRODUCER_HPP

#include "collectors/StatisticsCollector.hpp"

class StatisticsProducer
{
    public:

    StatisticsProducer();

    ~StatisticsProducer();

    const StatisticsProducerStruct& GetStatisticsCollectors() const;

    protected:

    StatisticsProducerStruct statistics_collectors;

};

#endif
