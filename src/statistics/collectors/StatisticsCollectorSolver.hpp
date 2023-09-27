#ifndef STATISTICS_COLLECTOR_SOLVER_HPP
#define STATISTICS_COLLECTOR_SOLVER_HPP

#include "StatisticsCollector.hpp"
#include "elements/StatisticsElementCounter.hpp"

class StatisticsCollectorSolver : public StatisticsCollector
{
    public:

    StatisticsCollectorSolver();

    ~StatisticsCollectorSolver();

    StatisticsElementCounter& games_played;
    StatisticsElementCounter& games_won;
    StatisticsElementCounter& games_lost;
    StatisticsElementCounter& games_abandoned;
    StatisticsElementCounter& uncovered_fields;
    StatisticsElementCounter& flagged_mines;

    protected:

    virtual StatisticsCollector* CreateNew() const override;
};

#endif
