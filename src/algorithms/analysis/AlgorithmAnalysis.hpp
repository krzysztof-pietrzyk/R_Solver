#ifndef ALGORITHM_ANALYSIS_HPP
#define ALGORITHM_ANALYSIS_HPP

// project includes
#include "../Algorithm.hpp"
#include "../../grid/GridAlgorithmIf.hpp"

// std includes

// forward declarations


class AlgorithmAnalysis : public Algorithm
{
    public:

    AlgorithmAnalysis(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmAnalysis();

    protected:

    const GridAlgorithmIf& grid;
    const CachedVector& visible;
    const CachedVector& flagged;
};

#endif
