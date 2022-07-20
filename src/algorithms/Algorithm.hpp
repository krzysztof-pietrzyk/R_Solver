#ifndef Algorithm_hpp
#define Algorithm_hpp

#include "grid/GridManager.hpp"

#include "AlgorithmDataStorage.hpp"
#include "AlgorithmMetrics.hpp"

enum AlgorithmStatus
{
    NO_STATUS,  // For algorithms which only analyze the board
    SUCCESS,  // At least one click performed
    NO_MOVES,  // No clicks were performed
    GAME_WON,  // Map is successfully cleared after this algorithm run and game is won
    GAME_LOST  // This algorithm run resulted in clicking on a mine and game is lost
};

class Algorithm
{
    /*
    Abstract base class for algorithm objects.
    Each algorithm has a Run() method, which executes the algorithm
    Algorithms have access to AlgorithmDataStorage and GridManager
    */
    public:

    AlgorithmMetrics metrics;
    
    Algorithm(GridManager& grid_, AlgorithmDataStorage& data_);

    ~Algorithm();

    virtual AlgorithmStatus Run();

    protected:

    GridManager& grid;

    AlgorithmDataStorage& data;

    virtual AlgorithmStatus RunInternal() = 0;

    virtual void LeftClick(unsigned int field);

    virtual void RightClick(unsigned int field);
};

#endif
