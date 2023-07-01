#include "AlgorithmGiveUp.hpp"

AlgorithmGiveUp::AlgorithmGiveUp(GridManager& grid_, AlgorithmDataStorage& data_)
    : AlgorithmDecision(grid_, data_),
    D_is_lost(GetModifiableGridManagerReference().is_lost)
{}

AlgorithmGiveUp::~AlgorithmGiveUp() {}

AlgorithmStatus AlgorithmGiveUp::Execution()
{
    D_is_lost = true;
    return AlgorithmStatus::NO_STATUS;
}
