#ifndef Algorithm_hpp
#define Algorithm_hpp

#include "grid/GridManager.hpp"
#include "AlgorithmDataStorage.hpp"

class Algorithm
{
    /*
    Abstract base class for algorithm objects.
    Each algorithm has a Run() method, which executes the algorithm
    Algorithms have access to AlgorithmDataStorage and GridManager
    */
    public:
    
    Algorithm(GridManager& grid_, AlgorithmDataStorage& data_);

    ~Algorithm();

    virtual bool Run() = 0;

    protected:

    GridManager& grid;

    AlgorithmDataStorage& data;
};

#endif
