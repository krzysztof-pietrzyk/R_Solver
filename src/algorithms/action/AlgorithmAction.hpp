#ifndef ALGORITHM_ACTION_HPP
#define ALGORITHM_ACTION_HPP

#include "../Algorithm.hpp"
#include "../../statistics/types/StatisticsTypeClicks.hpp"

class AlgorithmAction : public Algorithm
{
    /* 
    Abstract class for algorithms which take an action, 
    meaning they perform left or right clicks.
    The main difference from other algorithms is that this type of algorithm
    automatically checks whether the game is won/lost at the end.
    */
    public:

    AlgorithmAction(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmAction();

    AlgorithmStatus Run() override;

    protected:

    virtual void RunInternal() = 0;

    virtual bool LeftClick(const uint32_t field) const override;

    virtual bool RightClick(const uint32_t field) const override;

    private:

    StatisticsTypeClicks* statistics_clicks;

    AlgorithmStatus CheckGameOverConditions() const;

    AlgorithmStatus GetActionResult(const uint32_t clicks_difference) const;
};

#endif
