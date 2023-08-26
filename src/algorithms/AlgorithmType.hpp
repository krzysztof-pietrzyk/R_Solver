#ifndef ALGORITHM_TYPE_HPP
#define ALGORITHM_TYPE_HPP

#include "../utils/Label.hpp"

#include <stdexcept>

enum class AlgorithmType
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
    static const Label FIRST_MOVE               = "Algorithm: First Move";
    static const Label SIMPLE_CORNERS           = "Algorithm: Simple Corners";
    static const Label REFRESH_BORDER           = "Algorithm: Refresh Border";
    static const Label LAYER_ONE                = "Algorithm: Layer One";
    static const Label REFRESH_SECTIONS         = "Algorithm: Refresh Sections";
    static const Label LAYER_TWO                = "Algorithm: Layer Two";
    static const Label REFRESH_SEGMENTS         = "Algorithm: Refresh Segments";
    static const Label REFRESH_SUBSEGMENTS      = "Algorithm: Refresh Subsegments";
    static const Label REFRESH_FACE             = "Algorithm: Refresh Face";
    static const Label REFRESH_COMBINATIONS     = "Algorithm: Refresh Combinations";
    static const Label COMBINATIONS_SAFE_MOVES  = "Algorithm: Combinations Safe Moves";
    static const Label COMBINATIONS_LEAST_RISKY = "Algorithm: Combinations Least Risky";
    static const Label GIVE_UP                  = "Algorithm: Give Up";
}

static Label GetAlgorithmTypeLabel(AlgorithmType type)
{
    switch(type)
    {
        case AlgorithmType::UNHANDLED_ALGORITHM_TYPE:
            return Labels::Producers::Algorithms::UNHANDLED_ALGORITHM_TYPE;
        case AlgorithmType::FIRST_MOVE:
            return Labels::Producers::Algorithms::FIRST_MOVE;
        case AlgorithmType::SIMPLE_CORNERS:
            return Labels::Producers::Algorithms::SIMPLE_CORNERS;
        case AlgorithmType::REFRESH_BORDER:
            return Labels::Producers::Algorithms::REFRESH_BORDER;
        case AlgorithmType::LAYER_ONE:
            return Labels::Producers::Algorithms::LAYER_ONE;
        case AlgorithmType::REFRESH_SECTIONS:
            return Labels::Producers::Algorithms::REFRESH_SECTIONS;
        case AlgorithmType::LAYER_TWO:
            return Labels::Producers::Algorithms::LAYER_TWO;
        case AlgorithmType::REFRESH_SEGMENTS:
            return Labels::Producers::Algorithms::REFRESH_SEGMENTS;
        case AlgorithmType::REFRESH_SUBSEGMENTS:
            return Labels::Producers::Algorithms::REFRESH_SUBSEGMENTS;
        case AlgorithmType::REFRESH_FACE:
            return Labels::Producers::Algorithms::REFRESH_FACE;
        case AlgorithmType::REFRESH_COMBINATIONS:
            return Labels::Producers::Algorithms::REFRESH_COMBINATIONS;
        case AlgorithmType::COMBINATIONS_SAFE_MOVES:
            return Labels::Producers::Algorithms::COMBINATIONS_SAFE_MOVES;
        case AlgorithmType::COMBINATIONS_LEAST_RISKY:
            return Labels::Producers::Algorithms::COMBINATIONS_LEAST_RISKY;
        case AlgorithmType::GIVE_UP:
            return Labels::Producers::Algorithms::GIVE_UP;
        default:
            LOGGER_THROW("GetAlgorithmTypeLabel - Unhandled AlgorithmType");
    }
}

#endif
