#include "AlgorithmGiveUp.hpp"

AlgorithmGiveUp::AlgorithmGiveUp(GridAccessPlayerIf& grid_, AlgorithmDataTransfer& data_)
    : AlgorithmDecision(grid_, data_),
    D_grid(GetModifiableGridReference())
{
    LOGGER(LogLevel::INIT) << "AlgorithmGiveUp";
}

AlgorithmGiveUp::~AlgorithmGiveUp() {}

AlgorithmStatus AlgorithmGiveUp::Execution()
{
    D_grid.GiveUp();
    return AlgorithmStatus::NO_STATUS;
}
