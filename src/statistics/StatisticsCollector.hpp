#ifndef STATISTICS_COLLECTOR_HPP
#define STATISTICS_COLLECTOR_HPP

#include "types/StatisticsType.hpp"

class StatisticsCollector
{
    public:

    StatisticsCollector();

    StatisticsCollector(StatisticsType* statistics_type);

    ~StatisticsCollector();

    void SetStatisticsType(StatisticsType* statistics_type);

    virtual void Get(StatisticsType& output_data);

    protected:

    StatisticsType* statistics;
};

#endif
