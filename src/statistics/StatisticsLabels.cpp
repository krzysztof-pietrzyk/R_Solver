// implemented header
#include "StatisticsLabels.hpp"

// project includes
#include "../algorithms/AlgorithmType.hpp"

// std includes


Label GetAlgorithmTypeLabel(AlgorithmType type)
{
    Label return_label = Labels::Collectors::Algorithms::UNHANDLED_ALGORITHM_TYPE;
    switch(type)
    {
        case AlgorithmType::FIRST_MOVE:
            return_label = Labels::Collectors::Algorithms::FIRST_MOVE;
            break;
        case AlgorithmType::SIMPLE_CORNERS:
            return_label = Labels::Collectors::Algorithms::SIMPLE_CORNERS;
            break;
        case AlgorithmType::BORDER:
            return_label = Labels::Collectors::Algorithms::BORDER;
            break;
        case AlgorithmType::LAYER_ONE:
            return_label = Labels::Collectors::Algorithms::LAYER_ONE;
            break;
        case AlgorithmType::SECTIONS:
            return_label = Labels::Collectors::Algorithms::SECTIONS;
            break;
        case AlgorithmType::LAYER_TWO:
            return_label = Labels::Collectors::Algorithms::LAYER_TWO;
            break;
        case AlgorithmType::SEGMENTS:
            return_label = Labels::Collectors::Algorithms::SEGMENTS;
            break;
        case AlgorithmType::SUBSEGMENTS:
            return_label = Labels::Collectors::Algorithms::SUBSEGMENTS;
            break;
        case AlgorithmType::FACE:
            return_label = Labels::Collectors::Algorithms::FACE;
            break;
        case AlgorithmType::COMBINATIONS:
            return_label = Labels::Collectors::Algorithms::COMBINATIONS;
            break;
        case AlgorithmType::COMBINATIONS_SAFE_MOVES:
            return_label = Labels::Collectors::Algorithms::COMBINATIONS_SAFE_MOVES;
            break;
        case AlgorithmType::COMBINATIONS_LEAST_RISKY:
            return_label = Labels::Collectors::Algorithms::COMBINATIONS_LEAST_RISKY;
            break;
        case AlgorithmType::GIVE_UP:
            return_label = Labels::Collectors::Algorithms::GIVE_UP;
            break;
        case AlgorithmType::SIMPLE_ACTIONS:
            return_label = Labels::Collectors::Algorithms::SIMPLE_ACTIONS;
            break;
        default:
            break;
    }
    return return_label;
}
