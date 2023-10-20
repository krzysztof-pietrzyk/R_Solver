#include "AlgorithmAnalysis.hpp"

AlgorithmAnalysis::AlgorithmAnalysis(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : Algorithm(grid_, data_),
    grid(grid_)
{

}

AlgorithmAnalysis::~AlgorithmAnalysis()
{

}
