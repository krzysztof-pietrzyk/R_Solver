#ifndef ALGORITHM_DECISION_HPP
#define ALGORITHM_DECISION_HPP

#include "../../grid/GridAlgorithmIf.hpp"

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

    protected:

    const GridAlgorithmIf& grid;

    ActionsDTO& actions_dto;

    AlgorithmType algorithm_type;

    void QueueAction(uint32_t field, PlayerAction action);
};

#endif
