#ifndef AlgorithmManager_hpp
#define AlgorithmManager_hpp

#include <map>

#include "grid/GridManager.hpp"

#include "AlgorithmFactory.hpp"

class AlgorithmManager
{
    /*
    This class holds references to the algorithms and manages interactions between them.
    In other words, it defines in which order the algorithms should be executed.
    */
    public:

    AlgorithmManager(GridManager& grid_);

    ~AlgorithmManager();

    bool RunAll();

    bool RunAll2();

    private:

    GridManager* grid;
    AlgorithmFactory* factory;
    AlgorithmDataStorage* data;

    std::map<AlgorithmType, Algorithm*> algorithms;
};

#endif
