#ifndef ALGORITHM_LABELS_HPP
#define ALGORITHM_LABELS_HPP

// project includes
#include "AlgorithmType.hpp"
#include "../utils/Label.hpp"

// std includes

// forward declarations


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
    Label return_label = Labels::Producers::Algorithms::UNHANDLED_ALGORITHM_TYPE;
    switch(type)
    {
        case AlgorithmType::FIRST_MOVE:
            return_label = Labels::Producers::Algorithms::FIRST_MOVE;
            break;
        case AlgorithmType::SIMPLE_CORNERS:
            return_label = Labels::Producers::Algorithms::SIMPLE_CORNERS;
            break;
        case AlgorithmType::BORDER:
            return_label = Labels::Producers::Algorithms::BORDER;
            break;
        case AlgorithmType::LAYER_ONE:
            return_label = Labels::Producers::Algorithms::LAYER_ONE;
            break;
        case AlgorithmType::SECTIONS:
            return_label = Labels::Producers::Algorithms::SECTIONS;
            break;
        case AlgorithmType::LAYER_TWO:
            return_label = Labels::Producers::Algorithms::LAYER_TWO;
            break;
        case AlgorithmType::SEGMENTS:
            return_label = Labels::Producers::Algorithms::SEGMENTS;
            break;
        case AlgorithmType::SUBSEGMENTS:
            return_label = Labels::Producers::Algorithms::SUBSEGMENTS;
            break;
        case AlgorithmType::FACE:
            return_label = Labels::Producers::Algorithms::FACE;
            break;
        case AlgorithmType::COMBINATIONS:
            return_label = Labels::Producers::Algorithms::COMBINATIONS;
            break;
        case AlgorithmType::COMBINATIONS_SAFE_MOVES:
            return_label = Labels::Producers::Algorithms::COMBINATIONS_SAFE_MOVES;
            break;
        case AlgorithmType::COMBINATIONS_LEAST_RISKY:
            return_label = Labels::Producers::Algorithms::COMBINATIONS_LEAST_RISKY;
            break;
        case AlgorithmType::GIVE_UP:
            return_label = Labels::Producers::Algorithms::GIVE_UP;
            break;
        case AlgorithmType::SIMPLE_ACTIONS:
            return_label = Labels::Producers::Algorithms::SIMPLE_ACTIONS;
            break;
        default:
            break;
    }
    return return_label;
}

#endif
