#include "AlgorithmDecision.hpp"

AlgorithmDecision::AlgorithmDecision(GridAccessPlayerIf& grid_, AlgorithmDataStorage& data_)
    : Algorithm(grid_, data_),
    D_grid(GetModifiableGridReference())
{
    LOGGER(LOG_INIT) << "AlgorithmDecision";
}

AlgorithmDecision::~AlgorithmDecision() {}

AlgorithmStatus AlgorithmDecision::Run()
{
    const uint32_t number_of_clicks_before = left_click_counter + right_click_counter;
    Execution();
    const uint32_t number_of_clicks_after = left_click_counter + right_click_counter;
    
    AlgorithmStatus action_result = GetActionResult(number_of_clicks_after - number_of_clicks_before);
    AlgorithmStatus game_over_result = CheckGameOverConditions();

    if(game_over_result == AlgorithmStatus::NO_STATUS)
    {
        return action_result;
    }
    return game_over_result;
}

AlgorithmStatus AlgorithmDecision::CheckGameOverConditions() const
{
    if(grid.IsLost()) { return AlgorithmStatus::GAME_LOST; }
    else if(visible.Index() == grid.GetTotalSafeFields()) { return AlgorithmStatus::GAME_WON; }
    else return AlgorithmStatus::NO_STATUS;
}

AlgorithmStatus AlgorithmDecision::GetActionResult(const uint32_t clicks_difference) const
{
    if(clicks_difference > 0) { return AlgorithmStatus::SUCCESS; }
    return AlgorithmStatus::NO_MOVES;
}

bool AlgorithmDecision::LeftClick(const uint32_t field)
{
    PlayerActionResult result = D_grid.SetVisible(field);
    if(result == PlayerActionResult::CORRECT)
    {
        left_click_counter += 1;
    }
    return result;
}

bool AlgorithmDecision::RightClick(const uint32_t field)
{
    PlayerActionResult result = D_grid.SetFlag(field);
    if(result == PlayerActionResult::CORRECT)
    {
        right_click_counter += 1;
    }
    return result;
}
