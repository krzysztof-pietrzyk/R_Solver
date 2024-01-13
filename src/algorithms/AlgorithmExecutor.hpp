#ifndef ALGORITHM_EXECUTOR_HPP
#define ALGORITHM_EXECUTOR_HPP

// project includes
#include "AlgorithmTransitionManager.hpp"
#include "data/AlgorithmDataTransfer.hpp"

// std includes
#include <map>

// forward declarations
class GridAlgorithmIf;
class Algorithm;


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
