#ifndef ALGORITHM_EXECUTOR_HPP
#define ALGORITHM_EXECUTOR_HPP

#include "../utils/Logger.hpp"
#include "../grid/GridAlgorithmAnalysisIf.hpp"

#include "AlgorithmFactory.hpp"
#include "AlgorithmTransitionManager.hpp"

#include <map>

class AlgorithmExecutor
{
    public:

    AlgorithmExecutor(GridAlgorithmAnalysisIf& grid_);

    ~AlgorithmExecutor();

    void RunAll() const;

    const std::map<AlgorithmType, Algorithm*>& GetAlgorithmsMap() const;

    private:

    AlgorithmDataTransfer* data;
    AlgorithmTransitionManager transitions;

    std::map<AlgorithmType, Algorithm*> algorithms;  // pointers to all algorithms

    void CreateAlgorithms(GridAlgorithmAnalysisIf& grid);
};

#endif
