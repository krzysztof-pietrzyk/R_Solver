#ifndef AlgorithmManager_hpp
#define AlgorithmManager_hpp

#include <map>

#include "../grid/GridManager.hpp"

#include "AlgorithmFactory.hpp"
#include "AlgorithmTransitionManager.hpp"

class AlgorithmManager
{
    public:

    AlgorithmManager(GridManager& grid_);

    ~AlgorithmManager();

    bool RunAll() const;

    private:

    GridManager* grid;
    AlgorithmFactory* factory;
    AlgorithmDataStorage* data;
    AlgorithmTransitionManager transitions;

    std::map<AlgorithmType, Algorithm*> algorithms;  // pointers to all algorithms

    void CreateAlgorithms();
};

#endif
