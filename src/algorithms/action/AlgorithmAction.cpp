#include "AlgorithmAction.hpp"

AlgorithmAction::AlgorithmAction(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_, data_)
{
    statistics_clicks = new StatisticsCollectorClicks();
    statistics_collectors.push_back(statistics_clicks);
}

AlgorithmAction::~AlgorithmAction()
{
    delete statistics_clicks;
}

AlgorithmStatus AlgorithmAction::Run()
{
    const uint32_t number_of_clicks_before = grid.left_click_counter + grid.right_click_counter;
    RunInternal();
    const uint32_t number_of_clicks_after = grid.left_click_counter + grid.right_click_counter;
    
    AlgorithmStatus action_result = GetActionResult(number_of_clicks_after - number_of_clicks_before);
    AlgorithmStatus game_over_result = CheckGameOverConditions();

    if(game_over_result == AlgorithmStatus::NO_STATUS) { return action_result; }
    else return game_over_result;
}

AlgorithmStatus AlgorithmAction::CheckGameOverConditions() const
{
    if(grid.is_lost) { return AlgorithmStatus::GAME_LOST; }
    else if(grid.visible_fields_index == grid.NM) { return AlgorithmStatus::GAME_WON; }
    else return AlgorithmStatus::NO_STATUS;
}

AlgorithmStatus AlgorithmAction::GetActionResult(const uint32_t clicks_difference) const
{
    if(clicks_difference > 0) { return AlgorithmStatus::SUCCESS; }
    return AlgorithmStatus::NO_MOVES;
}

bool AlgorithmAction::LeftClick(const uint32_t field) const
{
    bool result = Algorithm::LeftClick(field);
    StatisticsCollectorClicks* ref = (StatisticsCollectorClicks*)statistics_clicks;
    ref->left_clicks += 1;
    if(!result)
    {
        ref->wasted_left_clicks += 1;
    }
    return result;
}

bool AlgorithmAction::RightClick(const uint32_t field) const
{
    bool result = Algorithm::RightClick(field);
    StatisticsCollectorClicks* ref = (StatisticsCollectorClicks*)statistics_clicks;
    ref->right_clicks += 1;
    if(!result)
    {
        ref->wasted_right_clicks += 1;
    }
    return result;
}
