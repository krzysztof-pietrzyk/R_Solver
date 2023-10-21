#include "AlgorithmGiveUp.hpp"

AlgorithmGiveUp::AlgorithmGiveUp(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : AlgorithmAction(grid_, data_)
{
    LOGGER(LogLevel::INIT) << "AlgorithmGiveUp";
}

AlgorithmGiveUp::~AlgorithmGiveUp() {}

AlgorithmStatus AlgorithmGiveUp::Execution()
{
    grid.GiveUp();
    return AlgorithmStatus::NO_STATUS;
}
