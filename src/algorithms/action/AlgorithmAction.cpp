#include "AlgorithmAction.hpp"

AlgorithmAction::AlgorithmAction(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_, data_)
{

}

AlgorithmAction::~AlgorithmAction() {}

AlgorithmResult AlgorithmAction::Run()
{
    AlgorithmResult action_result = RunInternal();
    AlgorithmResult game_over_result = CheckGameOverConditions();
    if(game_over_result == AlgorithmResult::NO_RESULT) return action_result;
    else return game_over_result;
}

AlgorithmResult AlgorithmAction::CheckGameOverConditions()
{
    if(grid.is_lost) return AlgorithmResult::GAME_LOST;
    else if(grid.visible_fields_index == grid.NM) return AlgorithmResult::GAME_WON;
    else return AlgorithmResult::NO_RESULT;
}
