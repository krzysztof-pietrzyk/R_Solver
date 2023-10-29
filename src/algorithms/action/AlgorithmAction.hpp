#ifndef ALGORITHM_ACTION_HPP
#define ALGORITHM_ACTION_HPP

#include "../../grid/GridAlgorithmIf.hpp"
#include "../../statistics/elements/StatisticsElementCounter.hpp"

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

    StatisticsElementCounter* counter_left_clicks;
    StatisticsElementCounter* counter_wasted_left_clicks;
    StatisticsElementCounter* counter_right_clicks;
    StatisticsElementCounter* counter_wasted_right_clicks;

    void CreateStatisticsElements();

    AlgorithmStatus CheckGameOverConditions() const;

    AlgorithmStatus GetExecutionResult(const uint32_t clicks_difference) const;

    AlgorithmStatus GetReturnStatus(AlgorithmStatus execution_result, AlgorithmStatus game_over_result) const;
};

#endif
