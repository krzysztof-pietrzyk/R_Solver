#include "AlgorithmAction.hpp"

AlgorithmAction::AlgorithmAction(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : Algorithm(grid_, data_),
    grid(grid_)
{
    LOGGER(LogLevel::INIT) << "AlgorithmAction";
    statistics_clicks = new StatisticsCollectorClicks();  // deleted in StatisticsProducer
    statistics_collectors.push_back(statistics_clicks);
    left_click_counter = 0U;
    right_click_counter = 0U;
}

AlgorithmAction::~AlgorithmAction()
{

}

AlgorithmStatus AlgorithmAction::Run()
{
    const uint64_t number_of_clicks_before = left_click_counter + right_click_counter;
    Execution();
    const uint64_t number_of_clicks_after = left_click_counter + right_click_counter;
    const uint64_t clicks_difference = number_of_clicks_after - number_of_clicks_before;
    
    AlgorithmStatus execution_result = GetExecutionResult(clicks_difference);
    AlgorithmStatus game_over_result = CheckGameOverConditions();
    AlgorithmStatus final_status = GetReturnStatus(execution_result, game_over_result);
    UpdateExecutionStatistics(final_status);
    return final_status;
}

AlgorithmStatus AlgorithmAction::CheckGameOverConditions() const
{
    if(grid.IsLost())
    {
        return AlgorithmStatus::GAME_LOST;
    }
    else if(grid.IsWon())
    {
        return AlgorithmStatus::GAME_WON;
    }
    return AlgorithmStatus::NO_STATUS;
}

AlgorithmStatus AlgorithmAction::GetExecutionResult(const uint32_t clicks_difference) const
{
    if(clicks_difference > 0)
    {
        return AlgorithmStatus::SUCCESS;
    }
    return AlgorithmStatus::NO_MOVES;
}

PlayerActionResult AlgorithmAction::LeftClick(const uint32_t field)
{
    PlayerActionResult result = grid.SetVisible(field);
    statistics_clicks->left_clicks += 1U;
    if(result == PlayerActionResult::CORRECT)
    {
        left_click_counter += 1U;
    }
    else if(result == PlayerActionResult::WASTED)
    {
        statistics_clicks->wasted_left_clicks += 1U;
    }
    return result;
}

PlayerActionResult AlgorithmAction::RightClick(const uint32_t field)
{
    PlayerActionResult result = grid.SetFlag(field);
    statistics_clicks->right_clicks += 1U;
    if(result == PlayerActionResult::CORRECT)
    {
        right_click_counter += 1U;
    }
    else if(result == PlayerActionResult::WASTED)
    {
        statistics_clicks->wasted_right_clicks += 1U;
    }
    return result;
}

AlgorithmStatus AlgorithmAction::GetReturnStatus(AlgorithmStatus execution_result, AlgorithmStatus game_over_result) const
{
    AlgorithmStatus return_status;
    if(game_over_result == AlgorithmStatus::NO_STATUS)
    {
        return_status = execution_result;
    }
    else
    {
        return_status = game_over_result;
    }
    return return_status;
}
