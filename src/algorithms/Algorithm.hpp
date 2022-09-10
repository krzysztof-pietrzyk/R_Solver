#ifndef Algorithm_hpp
#define Algorithm_hpp

#include "../grid/GridManager.hpp"
#include "AlgorithmDataStorage.hpp"

enum AlgorithmType
{
    ALGORITHM_SIMPLE_CORNERS,
    ALGORITHM_REFRESH_BORDER,
    ALGORITHM_LAYER_ONE,
    ALGORITHM_REFRESH_SECTIONS,
    ALGORITHM_LAYER_TWO,
    ALGORITHM_REFRESH_SEGMENTS,
    ALGORITHM_REFRESH_SUBSEGMENTS,
    ALGORITHM_REFRESH_FACE,
    ALGORITHM_REFRESH_COMBINATIONS,
    ALGORITHM_COMBINATIONS_SAFE_MOVES,
    ALGORITHM_COMBINATIONS_LEAST_RISKY
};

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
    
    Algorithm(GridManager& grid_, AlgorithmDataStorage& data_);

    ~Algorithm();

    virtual AlgorithmStatus Run() = 0;

    protected:

    GridManager& grid;

    AlgorithmDataStorage& data;
};

#endif
