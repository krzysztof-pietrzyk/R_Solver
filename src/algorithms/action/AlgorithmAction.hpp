#ifndef ALGORITHM_ACTION_HPP
#define ALGORITHM_ACTION_HPP

#include "../../grid/GridAlgorithmIf.hpp"
#include "../../statistics/collectors/StatisticsCollectorClicks.hpp"

#include "../Algorithm.hpp"

class AlgorithmAction : public Algorithm
{
    public:

    AlgorithmAction(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmAction();

    AlgorithmStatus Run() override;

    protected:

    GridAlgorithmIf& grid;

    PlayerActionResult LeftClick(const uint32_t field);

    PlayerActionResult RightClick(const uint32_t field);

    private:

    uint64_t left_click_counter;
    uint64_t right_click_counter;
    StatisticsCollectorClicks* statistics_clicks;

    AlgorithmStatus CheckGameOverConditions() const;

    AlgorithmStatus GetExecutionResult(const uint32_t clicks_difference) const;
};

#endif
