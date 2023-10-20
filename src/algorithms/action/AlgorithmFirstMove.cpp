#include "AlgorithmFirstMove.hpp"

const uint32_t AlgorithmFirstMove::default_first_move_field = 0;

AlgorithmFirstMove::AlgorithmFirstMove(GridAlgorithmAnalysisIf& grid_, AlgorithmDataTransfer& data_)
    : AlgorithmDecision(grid_, data_)
{
    LOGGER(LogLevel::INIT) << "AlgorithmFirstMove";
    first_move_field = default_first_move_field;
}

AlgorithmFirstMove::~AlgorithmFirstMove() {}

AlgorithmStatus AlgorithmFirstMove::Execution()
{
    LeftClick(first_move_field);
    return AlgorithmStatus::NO_STATUS;
}
