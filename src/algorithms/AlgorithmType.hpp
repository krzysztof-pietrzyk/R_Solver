#ifndef ALGORITHM_TYPE_HPP
#define ALGORITHM_TYPE_HPP

#include "../utils/Label.hpp"
#include "../utils/Logger.hpp"

enum class AlgorithmType
{
    UNHANDLED_ALGORITHM_TYPE,
    FIRST_MOVE,
    SIMPLE_CORNERS,
    BORDER,
    LAYER_ONE,
    SECTIONS,
    LAYER_TWO,
    SEGMENTS,
    SUBSEGMENTS,
    FACE,
    COMBINATIONS,
    COMBINATIONS_SAFE_MOVES,
    COMBINATIONS_LEAST_RISKY,
    GIVE_UP,
    SIMPLE_ACTIONS
};

namespace Labels::Producers::Algorithms
{
    static const Label UNHANDLED_ALGORITHM_TYPE = "Unhandled AlgorithmType";
    static const Label FIRST_MOVE               = "Action: First Move";
    static const Label SIMPLE_CORNERS           = "Decision: Simple Corners";
    static const Label BORDER                   = "Analysis: Border";
    static const Label LAYER_ONE                = "Decision: Layer One";
    static const Label SECTIONS                 = "Analysis: Sections";
    static const Label LAYER_TWO                = "Decision: Layer Two";
    static const Label SEGMENTS                 = "Analysis: Segments";
    static const Label SUBSEGMENTS              = "Analysis: Subsegments";
    static const Label FACE                     = "Analysis: Face";
    static const Label COMBINATIONS             = "Analysis: Combinations";
    static const Label COMBINATIONS_SAFE_MOVES  = "Decision: Combinations Safe Moves";
    static const Label COMBINATIONS_LEAST_RISKY = "Decision: Combinations Least Risky";
    static const Label GIVE_UP                  = "Action: Give Up";
    static const Label SIMPLE_ACTIONS           = "Action: Simple Actions";
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
        case AlgorithmType::BORDER:
            return Labels::Producers::Algorithms::BORDER;
        case AlgorithmType::LAYER_ONE:
            return Labels::Producers::Algorithms::LAYER_ONE;
        case AlgorithmType::SECTIONS:
            return Labels::Producers::Algorithms::SECTIONS;
        case AlgorithmType::LAYER_TWO:
            return Labels::Producers::Algorithms::LAYER_TWO;
        case AlgorithmType::SEGMENTS:
            return Labels::Producers::Algorithms::SEGMENTS;
        case AlgorithmType::SUBSEGMENTS:
            return Labels::Producers::Algorithms::SUBSEGMENTS;
        case AlgorithmType::FACE:
            return Labels::Producers::Algorithms::FACE;
        case AlgorithmType::COMBINATIONS:
            return Labels::Producers::Algorithms::COMBINATIONS;
        case AlgorithmType::COMBINATIONS_SAFE_MOVES:
            return Labels::Producers::Algorithms::COMBINATIONS_SAFE_MOVES;
        case AlgorithmType::COMBINATIONS_LEAST_RISKY:
            return Labels::Producers::Algorithms::COMBINATIONS_LEAST_RISKY;
        case AlgorithmType::GIVE_UP:
            return Labels::Producers::Algorithms::GIVE_UP;
        case AlgorithmType::SIMPLE_ACTIONS:
            return Labels::Producers::Algorithms::SIMPLE_ACTIONS;
        default:
            LOGGER_THROW("GetAlgorithmTypeLabel - Unhandled AlgorithmType");
    }
}

#endif
