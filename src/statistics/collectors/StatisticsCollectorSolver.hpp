#ifndef STATISTICS_COLLECTOR_SOLVER_HPP
#define STATISTICS_COLLECTOR_SOLVER_HPP

#include "StatisticsCollector.hpp"

class StatisticsCollectorSolver : public StatisticsCollector
{
    public:

    StatisticsCollectorSolver();

    ~StatisticsCollectorSolver();

    uint64_t& games_played;
    uint64_t& games_won;
    uint64_t& games_abandoned;
    uint64_t& uncovered_fields;

    protected:

    virtual StatisticsCollector* CreateNew() const override;
};

#endif
