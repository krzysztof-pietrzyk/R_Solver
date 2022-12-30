#ifndef STATISTICS_TYPE_SOLVER_HPP
#define STATISTICS_TYPE_SOLVER_HPP

#include "StatisticsType.hpp"

class StatisticsTypeSolver : public StatisticsType
{
    public:

    StatisticsTypeSolver();

    ~StatisticsTypeSolver();

    virtual std::string GetStatistics() const override;

    virtual void operator+= (const StatisticsType& other) override;

    virtual StatisticsType* Clone() const override;

    virtual void Clear() override;

    uint64_t games_played;
    uint64_t games_won;
    uint64_t games_abandoned;
    uint64_t uncovered_fields;
};

#endif
