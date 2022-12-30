#ifndef STATISTICS_TYPE_SOLVER_HPP
#define STATISTICS_TYPE_SOLVER_HPP

#include "StatisticsType.hpp"

class StatisticsTypeSolver : public StatisticsType
{
    public:

    StatisticsTypeSolver();

    ~StatisticsTypeSolver();

    uint64_t& games_played;
    uint64_t& games_won;
    uint64_t& games_abandoned;
    uint64_t& uncovered_fields;

    protected:

    virtual StatisticsType* CreateNew() const override;
};

#endif
