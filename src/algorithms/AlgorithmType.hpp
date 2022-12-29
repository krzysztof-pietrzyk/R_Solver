#ifndef ALGORITHM_TYPE_HPP
#define ALGORITHM_TYPE_HPP

#include <string>
#include <stdexcept>

enum AlgorithmType
{
    UNHANDLED_TYPE,
    FIRST_MOVE,
    SIMPLE_CORNERS,
    REFRESH_BORDER,
    LAYER_ONE,
    REFRESH_SECTIONS,
    LAYER_TWO,
    REFRESH_SEGMENTS,
    REFRESH_SUBSEGMENTS,
    REFRESH_FACE,
    REFRESH_COMBINATIONS,
    COMBINATIONS_SAFE_MOVES,
    COMBINATIONS_LEAST_RISKY,
    GIVE_UP
};

static std::string GetAlgorithmTypeLabel(AlgorithmType type)
{
    switch(type)
    {
        case UNHANDLED_TYPE:
            return "Unhandled AlgorithmType";
        case FIRST_MOVE:
            return "First Move";
        case SIMPLE_CORNERS:
            return "Simple Corners";
        case REFRESH_BORDER:
            return "Refresh Border";
        case LAYER_ONE:
            return "Layer One";
        case REFRESH_SECTIONS:
            return "Refresh Sections";
        case LAYER_TWO:
            return "Layer Two";
        case REFRESH_SEGMENTS:
            return "Refresh Segments";
        case REFRESH_SUBSEGMENTS:
            return "Refresh Subsegments";
        case REFRESH_FACE:
            return "Refresh Face";
        case REFRESH_COMBINATIONS:
            return "Refresh Combinations";
        case COMBINATIONS_SAFE_MOVES:
            return "Combinations Safe Moves";
        case COMBINATIONS_LEAST_RISKY:
            return "Combinations Least Risky";
        case GIVE_UP:
            return "Give Up";
        default:
            throw std::runtime_error("ERROR: GetAlgorithmTypeLabel(AlgorithmType): Unhandled AlgorithmType!");
    }
}

#endif
