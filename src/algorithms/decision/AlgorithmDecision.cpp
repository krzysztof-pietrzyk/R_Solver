#include "AlgorithmDecision.hpp"

AlgorithmDecision::AlgorithmDecision(GridAccessPlayerIf& grid_, AlgorithmDataTransfer& data_)
    : Algorithm(grid_, data_),
    D_grid(GetModifiableGridReference())
{
    LOGGER(LogLevel::INIT) << "AlgorithmDecision";
    statistics_clicks = new StatisticsCollectorClicks();  // deleted in StatisticsProducer
    statistics_collectors.push_back(statistics_clicks);
}

AlgorithmDecision::~AlgorithmDecision() {}

AlgorithmStatus AlgorithmDecision::Run()
{
    const uint64_t number_of_clicks_before = left_click_counter + right_click_counter;
    Execution();
    statistics_executions->executions += 1;
    const uint64_t number_of_clicks_after = left_click_counter + right_click_counter;
    
    AlgorithmStatus action_result = GetActionResult(number_of_clicks_after - number_of_clicks_before);
    AlgorithmStatus game_over_result = CheckGameOverConditions();

    if(game_over_result == AlgorithmStatus::NO_STATUS)
    {
        return action_result;
    }
    else if(game_over_result == AlgorithmStatus::GAME_LOST)
    {
        statistics_clicks->times_caused_loss += 1;
    }
    return game_over_result;
}

AlgorithmStatus AlgorithmDecision::CheckGameOverConditions() const
{
    if(grid.IsLost())
    {
        return AlgorithmStatus::GAME_LOST;
    }
    else if(visible.Index() == grid_dim.safe)
    {
        return AlgorithmStatus::GAME_WON;
    }
    return AlgorithmStatus::NO_STATUS;
}

AlgorithmStatus AlgorithmDecision::GetActionResult(const uint32_t clicks_difference) const
{
    if(clicks_difference > 0)
    {
        return AlgorithmStatus::SUCCESS;
    }
    return AlgorithmStatus::NO_MOVES;
}

PlayerActionResult AlgorithmDecision::LeftClick(const uint32_t field)
{
    PlayerActionResult result = D_grid.SetVisible(field);
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

PlayerActionResult AlgorithmDecision::RightClick(const uint32_t field)
{
    PlayerActionResult result = D_grid.SetFlag(field);
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
