#ifndef STATISTICS_TYPE_HPP
#define STATISTICS_TYPE_HPP

#include "../StatisticsStructs.hpp"
#include "../StatisticsLabels.hpp"

class StatisticsCollector
{
    public:

    StatisticsCollector(StatisticsCollectorStruct init_struct);
    ~StatisticsCollector();

    virtual void Enable();
    virtual void Disable();
    void Clear();

    const StatisticsCollectorStruct& GetStatistics() const;

    StatisticsCollector* Clone() const;

    void FlushToOutput(StatisticsCollector& output);
    void operator= (const StatisticsCollector& other);

    protected:

    StatisticsCollectorStruct labelled_data_elements;

    virtual StatisticsCollector* CreateNew() const = 0;

    void _DoNothing(...);
};

#endif
