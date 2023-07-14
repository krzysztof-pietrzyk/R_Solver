#ifndef ALGORITHM_TYPE_HPP
#define ALGORITHM_TYPE_HPP

#include "../utils/Label.hpp"

#include <stdexcept>

enum AlgorithmType
{
    UNHANDLED_ALGORITHM_TYPE,
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

namespace Labels::Producers::Algorithms
{
    static const Label UNHANDLED_ALGORITHM_TYPE = "Unhandled AlgorithmType";
    static const Label FIRST_MOVE = "First Move";
    static const Label SIMPLE_CORNERS = "Simple Corners";
    static const Label REFRESH_BORDER = "Refresh Border";
    static const Label LAYER_ONE = "Layer One";
    static const Label REFRESH_SECTIONS = "Refresh Sections";
    static const Label LAYER_TWO = "Layer Two";
    static const Label REFRESH_SEGMENTS = "Refresh Segments";
    static const Label REFRESH_SUBSEGMENTS = "Refresh Subsegments";
    static const Label REFRESH_FACE = "Refresh Face";
    static const Label REFRESH_COMBINATIONS = "Refresh Combinations";
    static const Label COMBINATIONS_SAFE_MOVES = "Combinations Safe Moves";
    static const Label COMBINATIONS_LEAST_RISKY = "Combinations Least Risky";
    static const Label GIVE_UP = "Give Up";
}

static Label GetAlgorithmTypeLabel(AlgorithmType type)
{
    switch(type)
    {
        case UNHANDLED_ALGORITHM_TYPE: return Labels::Producers::Algorithms::UNHANDLED_ALGORITHM_TYPE;
        case FIRST_MOVE:               return Labels::Producers::Algorithms::FIRST_MOVE;
        case SIMPLE_CORNERS:           return Labels::Producers::Algorithms::SIMPLE_CORNERS;
        case REFRESH_BORDER:           return Labels::Producers::Algorithms::REFRESH_BORDER;
        case LAYER_ONE:                return Labels::Producers::Algorithms::LAYER_ONE;
        case REFRESH_SECTIONS:         return Labels::Producers::Algorithms::REFRESH_SECTIONS;
        case LAYER_TWO:                return Labels::Producers::Algorithms::LAYER_TWO;
        case REFRESH_SEGMENTS:         return Labels::Producers::Algorithms::REFRESH_SEGMENTS;
        case REFRESH_SUBSEGMENTS:      return Labels::Producers::Algorithms::REFRESH_SUBSEGMENTS;
        case REFRESH_FACE:             return Labels::Producers::Algorithms::REFRESH_FACE;
        case REFRESH_COMBINATIONS:     return Labels::Producers::Algorithms::REFRESH_COMBINATIONS;
        case COMBINATIONS_SAFE_MOVES:  return Labels::Producers::Algorithms::COMBINATIONS_SAFE_MOVES;
        case COMBINATIONS_LEAST_RISKY: return Labels::Producers::Algorithms::COMBINATIONS_LEAST_RISKY;
        case GIVE_UP:                  return Labels::Producers::Algorithms::GIVE_UP;
        default:
            throw std::runtime_error("ERROR: GetAlgorithmTypeLabel(AlgorithmType): Unhandled AlgorithmType!");
    }
}

#endif
