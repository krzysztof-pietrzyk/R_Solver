#ifndef STATISTICS_PRODUCER_HPP
#define STATISTICS_PRODUCER_HPP

#include "types/StatisticsType.hpp"

#include <vector>

class StatisticsProducer
{
    public:

    StatisticsProducer();

    ~StatisticsProducer();

    const StatisticsProducerStruct& GetStatisticsTypes() const;

    protected:

    StatisticsProducerStruct statistics_types;

};

#endif

