#ifndef ALGORITHM_SIMPLE_ACTIONS_HPP
#define ALGORITHM_SIMPLE_ACTIONS_HPP

// project includes
#include "AlgorithmAction.hpp"

// std includes

// forward declarations
class StatisticsElementCounter;


class AlgorithmSimpleActions : public AlgorithmAction
{
    public:

    AlgorithmSimpleActions(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmSimpleActions();

    protected:

    AlgorithmStatus Execution() override;

    private:

    ActionsDTO& actions_dto;

    StatisticsElementCounter* counter_loss_simple_corners;
    StatisticsElementCounter* counter_loss_combinations_least_risky;
    StatisticsElementCounter* counter_loss_other;

    void CreateStatisticsElements();

    void UpdateLossStatistics(AlgorithmType algorithm_type);
};

#endif
