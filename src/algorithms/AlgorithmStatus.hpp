#ifndef ALGORITHM_STATUS_HPP
#define ALGORITHM_STATUS_HPP

enum class AlgorithmStatus
{
    UNHANDLED_STATUS,  // For testing and debugging purposes
    NO_STATUS,         // For algorithms which only analyze the board
    SUCCESS,           // At least one click performed
    NO_MOVES,          // No clicks were performed
    FAILURE,           // Something went wrong
    GAME_WON,          // Map is successfully cleared after this algorithm run and game is won
    GAME_LOST          // This algorithm run resulted in clicking on a mine and game is lost
};

#endif
