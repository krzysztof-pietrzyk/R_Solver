#include "AlgorithmFirstMove.hpp"

const uint32_t AlgorithmFirstMove::default_first_move_field = 0;

AlgorithmFirstMove::AlgorithmFirstMove(GridAccessPlayerIf& grid_, AlgorithmDataStorage& data_)
    : AlgorithmDecision(grid_, data_)
{
    first_move_field = default_first_move_field;
}

AlgorithmFirstMove::~AlgorithmFirstMove() {}

AlgorithmStatus AlgorithmFirstMove::Execution()
{
    LeftClick(first_move_field);
    return AlgorithmStatus::NO_STATUS;
}
