#ifndef ALGORITHM_DECISION_HPP
#define ALGORITHM_DECISION_HPP

#include "../../grid/GridAlgorithmIf.hpp"
#include "../../statistics/elements/StatisticsElementCounter.hpp"

#include "../AlgorithmType.hpp"
#include "../Algorithm.hpp"

class AlgorithmDecision : public Algorithm
{
    /* 
    Abstract class for algorithms which take a decision, 
    meaning they decide which fields are safe and which are not.
    */
    public:

    AlgorithmDecision(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmDecision();

    AlgorithmStatus Run() override;

    protected:

    const GridAlgorithmIf& grid;
    const CachedVector& visible;
    const CachedVector& flagged;

    ActionsDTO& actions_dto;

    // Overwrite it in inheriting classes
    AlgorithmType algorithm_type;

    void QueueAction(uint32_t field, PlayerAction action);

    private:

    StatisticsElementCounter* decisions_left_click;
    StatisticsElementCounter* decisions_right_click;

    void CreateStatisticsElements();
};

#endif
