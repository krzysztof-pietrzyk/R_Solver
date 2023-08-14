#ifndef ALGORITHM_MANAGER_HPP
#define ALGORITHM_MANAGER_HPP

#include "../utils/Logger.hpp"
#include "../grid/GridAccessPlayerIf.hpp"

#include "AlgorithmFactory.hpp"
#include "AlgorithmTransitionManager.hpp"

#include <map>

class AlgorithmManager
{
    public:

    AlgorithmManager(GridAccessPlayerIf& grid_);

    ~AlgorithmManager();

    bool RunAll() const;

    const std::map<AlgorithmType, Algorithm*>& GetAlgorithmsMap() const;

    private:

    GridAccessPlayerIf* grid;
    AlgorithmDataStorage* data;
    AlgorithmTransitionManager transitions;

    std::map<AlgorithmType, Algorithm*> algorithms;  // pointers to all algorithms

    void CreateAlgorithms();
};

#endif
