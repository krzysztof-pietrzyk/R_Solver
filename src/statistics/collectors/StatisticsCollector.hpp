#ifndef STATISTICS_TYPE_HPP
#define STATISTICS_TYPE_HPP

#include "../StatisticsLabels.hpp"

#include <cstdint>
#include <map>
#include <vector>

class StatisticsCollector;
typedef std::map<Label, uint64_t> StatisticsCollectorStruct;
typedef std::vector<StatisticsCollector*> StatisticsProducerStruct;
typedef std::map<Label, StatisticsProducerStruct> StatisticsAggregatorStruct;

class StatisticsCollector
{
    public:

    StatisticsCollector();
    ~StatisticsCollector();

    const StatisticsCollectorStruct& GetStatistics() const;

    void operator+= (const StatisticsCollector& other);

    StatisticsCollector* Clone() const;

    void Clear();

    StatisticsCollectorStruct labelled_data_elements;

    protected:

    virtual StatisticsCollector* CreateNew() const = 0;
};

#endif
