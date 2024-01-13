#ifndef ALGORITHM_DECISION_HPP
#define ALGORITHM_DECISION_HPP

// project includes
#include "../Algorithm.hpp"
#include "../AlgorithmType.hpp"
#include "../PlayerAction.hpp"
#include "../../grid/GridAlgorithmIf.hpp"

// std includes

// forward declarations
class StatisticsElementCounter;


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

    // This is to provide information about which Algorithm decided to perform
    // which actions. It's used by Action Algorithms
    // Overwrite it in inheriting classes
    AlgorithmType algorithm_type;

    void QueueAction(uint32_t field, PlayerAction action);

    private:

    StatisticsElementCounter* decisions_left_click;
    StatisticsElementCounter* decisions_right_click;

    void CreateStatisticsElements();
};

#endif
