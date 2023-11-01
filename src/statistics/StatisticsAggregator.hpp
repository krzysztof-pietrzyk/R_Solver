#ifndef STATISTICS_AGGREGATOR_HPP
#define STATISTICS_AGGREGATOR_HPP

// project includes
#include "../utils/Label.hpp"

// std includes
#include <map>
#include <string>

// forward declarations
class StatisticsProducer;


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
