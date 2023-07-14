#ifndef ALGORITHM_DECISION_HPP
#define ALGORITHM_DECISION_HPP

#include "../Algorithm.hpp"
#include "../../statistics/collectors/StatisticsCollectorClicks.hpp"

class AlgorithmDecision : public Algorithm
{
    /* 
    Abstract class for algorithms which take a decision, 
    meaning they decide which fields are safe and which are not.
    */
    public:

    AlgorithmDecision(GridAccessPlayerIf& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmDecision();

    AlgorithmStatus Run() override;

    protected:

    virtual bool LeftClick(const uint32_t field) const override;

    virtual bool RightClick(const uint32_t field) const override;

    private:

    StatisticsCollectorClicks* statistics_clicks;

    AlgorithmStatus CheckGameOverConditions() const;

    AlgorithmStatus GetActionResult(const uint32_t clicks_difference) const;
};

#endif
