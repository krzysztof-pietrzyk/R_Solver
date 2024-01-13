// implemented header
#include "AlgorithmFirstMove.hpp"

// project includes

// std includes


const uint32_t AlgorithmFirstMove::first_move_field = 0U;

AlgorithmFirstMove::AlgorithmFirstMove(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : AlgorithmAction(grid_, data_)
{
    LOGGER(LogLevel::INIT) << "AlgorithmFirstMove";
}

AlgorithmFirstMove::~AlgorithmFirstMove() {}

AlgorithmStatus AlgorithmFirstMove::Execution()
{
    LeftClick(first_move_field);
    return AlgorithmStatus::NO_STATUS;
}
