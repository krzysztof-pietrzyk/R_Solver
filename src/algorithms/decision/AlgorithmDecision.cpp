#include "AlgorithmDecision.hpp"

AlgorithmDecision::AlgorithmDecision(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_, data_)
{
    statistics_clicks = new StatisticsCollectorClicks();  // deleted in StatisticsProducer
    statistics_collectors.push_back(statistics_clicks);
}

AlgorithmDecision::~AlgorithmDecision()
{

}

AlgorithmStatus AlgorithmDecision::Run()
{
    statistics_executions->executions += 1;
    const uint32_t number_of_clicks_before = grid.left_click_counter + grid.right_click_counter;
    Execution();
    const uint32_t number_of_clicks_after = grid.left_click_counter + grid.right_click_counter;
    
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
    if(grid.is_lost) { return AlgorithmStatus::GAME_LOST; }
    else if(grid.visible_fields_index == grid.NM) { return AlgorithmStatus::GAME_WON; }
    else return AlgorithmStatus::NO_STATUS;
}

AlgorithmStatus AlgorithmDecision::GetActionResult(const uint32_t clicks_difference) const
{
    if(clicks_difference > 0) { return AlgorithmStatus::SUCCESS; }
    return AlgorithmStatus::NO_MOVES;
}

bool AlgorithmDecision::LeftClick(const uint32_t field) const
{
    bool result = Algorithm::LeftClick(field);
    statistics_clicks->left_clicks += 1;
    if(!result)
    {
        statistics_clicks->wasted_left_clicks += 1;
    }
    return result;
}

bool AlgorithmDecision::RightClick(const uint32_t field) const
{
    bool result = Algorithm::RightClick(field);
    statistics_clicks->right_clicks += 1;
    if(!result)
    {
        statistics_clicks->wasted_right_clicks += 1;
    }
    return result;
}
