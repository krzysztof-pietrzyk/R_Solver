#ifndef STATISTICS_COLLECTOR_ACTIONS_LOSS_HPP
#define STATISTICS_COLLECTOR_ACTIONS_LOSS_HPP

#include "StatisticsCollector.hpp"
#include "elements/StatisticsElementCounter.hpp"

class StatisticsCollectorActionsLoss : public StatisticsCollector
{
    public:

    StatisticsCollectorActionsLoss();

    ~StatisticsCollectorActionsLoss();

    StatisticsElementCounter& loss_simple_corners;
    StatisticsElementCounter& loss_combinations_least_risky;
    StatisticsElementCounter& loss_other;

    protected:

    virtual StatisticsCollector* CreateNew() const override;
};

#endif
