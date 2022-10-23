#include "AlgorithmGiveUp.hpp"

AlgorithmGiveUp::AlgorithmGiveUp(GridManager& grid_, AlgorithmDataStorage& data_)
    : AlgorithmAction(grid_, data_),
    D_is_lost(GetModifiableGridManagerReference().is_lost)
{}

AlgorithmGiveUp::~AlgorithmGiveUp() {}

void AlgorithmGiveUp::RunInternal()
{
    D_is_lost = true;
}
