// implemented header
#include "AlgorithmGiveUp.hpp"

// project includes

// std includes


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
