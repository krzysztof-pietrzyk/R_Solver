#ifndef Algorithm_hpp
#define Algorithm_hpp

#include "grid/GridManager.hpp"
#include "AlgorithmDataStorage.hpp"

enum AlgorithmResult
{
    SUCCESS,  // At least one click performed
    NO_MOVES,  // No clicks were performed
    NO_RESULT  // For algorithms which only analyze the board
};

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

    virtual AlgorithmResult Run() = 0;

    protected:

    GridManager& grid;

    AlgorithmDataStorage& data;
};

#endif
