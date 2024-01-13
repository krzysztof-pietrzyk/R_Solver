// implemented header
#include "AlgorithmAnalysis.hpp"

// project includes

// std includes


AlgorithmAnalysis::AlgorithmAnalysis(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : Algorithm(grid_, data_),
    grid(grid_),
    visible(grid_.GetVisibleFields()),
    flagged(grid_.GetFlaggedFields())
{
    LOGGER(LogLevel::INIT) << "AlgorithmAnalysis";
}

AlgorithmAnalysis::~AlgorithmAnalysis()
{

}
