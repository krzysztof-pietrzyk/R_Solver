#ifndef ALGORITHM_ANALYSIS_HPP
#define ALGORITHM_ANALYSIS_HPP

#include "../../grid/GridAlgorithmAnalysisIf.hpp"

#include "../Algorithm.hpp"

class AlgorithmAnalysis : public Algorithm
{
    public:

    AlgorithmAnalysis(GridAlgorithmAnalysisIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmAnalysis();

    AlgorithmStatus Run() override;

    protected:

    const GridAlgorithmAnalysisIf& grid;
};

#endif
