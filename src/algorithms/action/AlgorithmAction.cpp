#include "AlgorithmAction.hpp"

AlgorithmAction::AlgorithmAction(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_, data_)
{

}

AlgorithmAction::~AlgorithmAction() {}

AlgorithmStatus AlgorithmAction::Run()
{
    AlgorithmStatus action_result = RunInternal();
    AlgorithmStatus game_over_result = CheckGameOverConditions();
    if(game_over_result == AlgorithmStatus::NO_STATUS) return action_result;
    else return game_over_result;
}

AlgorithmStatus AlgorithmAction::CheckGameOverConditions()
{
    if(grid.is_lost) return AlgorithmStatus::GAME_LOST;
    else if(grid.visible_fields_index == grid.NM) return AlgorithmStatus::GAME_WON;
    else return AlgorithmStatus::NO_STATUS;
}
