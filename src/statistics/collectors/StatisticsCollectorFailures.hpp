#ifndef STATISTICS_COLLECTOR_FAILURES_HPP
#define STATISTICS_COLLECTOR_FAILURES_HPP

#include "StatisticsCollector.hpp"
#include "elements/StatisticsElementCounter.hpp"

class StatisticsCollectorFailures : public StatisticsCollector
{
    public:

    StatisticsCollectorFailures();

    ~StatisticsCollectorFailures();

    StatisticsElementCounter& failures;

    protected:

    virtual StatisticsCollector* CreateNew() const override;
};

#endif
