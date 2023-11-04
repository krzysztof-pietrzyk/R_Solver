#ifndef STATISTICS_AGGREGATOR_HPP
#define STATISTICS_AGGREGATOR_HPP

// project includes
#include "../utils/Label.hpp"

// std includes
#include <map>
#include <string>

// forward declarations
class StatisticsCollector;


class StatisticsAggregator
{
    public:

    StatisticsAggregator();

    ~StatisticsAggregator();

    void RegisterStatisticsCollector(Label collector_label, const StatisticsCollector* statistics_collector);

    StatisticsAggregator* Clone() const;

    std::string String() const;

    void FlushToOutput(StatisticsAggregator* output) const;

    protected:

    std::map<Label, const StatisticsCollector*> labelled_collectors;
};

#endif
