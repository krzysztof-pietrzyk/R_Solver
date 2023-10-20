#ifndef ALGORITHM_EXECUTOR_HPP
#define ALGORITHM_EXECUTOR_HPP

#include "../utils/Logger.hpp"
#include "../grid/GridAlgorithmIf.hpp"

#include "AlgorithmFactory.hpp"
#include "AlgorithmTransitionManager.hpp"

#include <map>

class AlgorithmExecutor
{
    public:

    AlgorithmExecutor(GridAlgorithmIf& grid_);

    ~AlgorithmExecutor();

    void RunAll() const;

    const std::map<AlgorithmType, Algorithm*>& GetAlgorithmsMap() const;

    private:

    AlgorithmDataTransfer* data;
    AlgorithmTransitionManager transitions;

    std::map<AlgorithmType, Algorithm*> algorithms;  // pointers to all algorithms

    void CreateAlgorithms(GridAlgorithmIf& grid);
};

#endif
