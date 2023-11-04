#ifndef STATISTICS_PRODUCER_HPP
#define STATISTICS_PRODUCER_HPP

// project includes

// std includes
#include <string>

// forward declarations
class StatisticsCollector;


class StatisticsProducer
{
    public:

    StatisticsProducer();

    ~StatisticsProducer();

    const StatisticsCollector* GetStatisticsCollector();

    protected:

    StatisticsCollector* statistics_collector;
};

#endif
