#include "AlgorithmGiveUp.hpp"

AlgorithmGiveUp::AlgorithmGiveUp(GridManager& grid_, AlgorithmDataStorage& data_) : AlgorithmAction(grid_, data_) {}

AlgorithmGiveUp::~AlgorithmGiveUp() {}

void AlgorithmGiveUp::RunInternal()
{
    grid.is_lost = true;
}
