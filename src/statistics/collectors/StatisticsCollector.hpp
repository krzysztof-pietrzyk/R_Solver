#ifndef STATISTICS_TYPE_HPP
#define STATISTICS_TYPE_HPP

#include "../StatisticsLabels.hpp"
#include "elements/StatisticsElement.hpp"

#include <map>
#include <vector>

class StatisticsCollector;
typedef std::map<Label, StatisticsElement*> StatisticsCollectorStruct;
typedef std::vector<StatisticsCollector*> StatisticsProducerStruct;
typedef std::map<Label, StatisticsProducerStruct> StatisticsAggregatorStruct;

class StatisticsCollector
{
    public:

    StatisticsCollector(StatisticsCollectorStruct init_struct);
    ~StatisticsCollector();

    virtual void Enable();
    virtual void Disable();
    void Clear();

    void operator+= (const StatisticsCollector& other);
    void operator= (const StatisticsCollector& other);

    const StatisticsCollectorStruct& GetStatistics() const;

    StatisticsCollector* Clone() const;

    protected:

    StatisticsCollectorStruct labelled_data_elements;

    virtual StatisticsCollector* CreateNew() const = 0;

    void _DoNothing(...);
};

#endif
