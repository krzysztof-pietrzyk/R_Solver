#ifndef STATISTICS_COLLECTOR_EXECUTIONS_HPP
#define STATISTICS_COLLECTOR_EXECUTIONS_HPP

#include "StatisticsCollector.hpp"
#include "elements/StatisticsElementUINT64.hpp"

class StatisticsCollectorExecutions : public StatisticsCollector
{
    public:

    StatisticsCollectorExecutions();

    ~StatisticsCollectorExecutions();

    StatisticsElementUINT64& executions;

    protected:

    virtual StatisticsCollector* CreateNew() const override;
};

#endif
