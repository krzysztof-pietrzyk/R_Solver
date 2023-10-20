#ifndef ALGORITHM_ANALYSIS_HPP
#define ALGORITHM_ANALYSIS_HPP

#include "../../grid/GridAlgorithmIf.hpp"

#include "../Algorithm.hpp"

class AlgorithmAnalysis : public Algorithm
{
    public:

    AlgorithmAnalysis(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmAnalysis();

    protected:

    const GridAlgorithmIf& grid;
};

#endif
