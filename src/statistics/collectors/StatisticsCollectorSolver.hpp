#ifndef STATISTICS_COLLECTOR_SOLVER_HPP
#define STATISTICS_COLLECTOR_SOLVER_HPP

#include "StatisticsCollector.hpp"
#include "elements/StatisticsElementUINT64.hpp"

class StatisticsCollectorSolver : public StatisticsCollector
{
    public:

    StatisticsCollectorSolver();

    ~StatisticsCollectorSolver();

    StatisticsElementUINT64& games_played;
    StatisticsElementUINT64& games_won;
    StatisticsElementUINT64& games_abandoned;
    StatisticsElementUINT64& uncovered_fields;
    StatisticsElementUINT64& flagged_mines;

    protected:

    virtual StatisticsCollector* CreateNew() const override;
};

#endif
