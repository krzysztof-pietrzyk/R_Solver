#ifndef STATISTICS_COLLECTOR_DECISIONS_HPP
#define STATISTICS_COLLECTOR_DECISIONS_HPP

#include "StatisticsCollector.hpp"
#include "elements/StatisticsElementCounter.hpp"

class StatisticsCollectorDecisions : public StatisticsCollector
{
    public:

    StatisticsCollectorDecisions();

    ~StatisticsCollectorDecisions();

    StatisticsElementCounter& decisions_left_click;
    StatisticsElementCounter& decisions_right_click;

    protected:

    virtual StatisticsCollector* CreateNew() const override;
};

#endif
