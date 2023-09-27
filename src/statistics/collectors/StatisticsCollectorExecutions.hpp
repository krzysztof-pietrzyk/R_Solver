#ifndef STATISTICS_COLLECTOR_EXECUTIONS_HPP
#define STATISTICS_COLLECTOR_EXECUTIONS_HPP

#include "StatisticsCollector.hpp"
#include "elements/StatisticsElementCounter.hpp"

class StatisticsCollectorExecutions : public StatisticsCollector
{
    public:

    StatisticsCollectorExecutions();

    ~StatisticsCollectorExecutions();

    StatisticsElementCounter& executions;

    protected:

    virtual StatisticsCollector* CreateNew() const override;
};

#endif
