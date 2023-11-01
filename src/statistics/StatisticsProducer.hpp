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

    StatisticsProducer* Clone() const;

    std::string String() const;

    void FlushToOutput(StatisticsProducer* output) const;

    protected:

    StatisticsCollector* statistics_collector;
};

#endif
