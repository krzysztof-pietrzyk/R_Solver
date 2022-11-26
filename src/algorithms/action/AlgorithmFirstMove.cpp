#include "AlgorithmFirstMove.hpp"

const uint32_t AlgorithmFirstMove::default_first_move_field = 0;

AlgorithmFirstMove::AlgorithmFirstMove(GridManager& grid_, AlgorithmDataStorage& data_)
    : AlgorithmAction(grid_, data_)
{
    first_move_field = default_first_move_field;
}

AlgorithmFirstMove::~AlgorithmFirstMove() {}

void AlgorithmFirstMove::RunInternal()
{
    LeftClick(first_move_field);
}