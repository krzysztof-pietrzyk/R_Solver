#include "AlgorithmFactory.hpp"

Algorithm* AlgorithmFactory::Create(AlgorithmType type, GridAlgorithmIf& grid, AlgorithmDataTransfer& data)
{
    switch(type)
    {
        case AlgorithmType::BORDER:
            return new AlgorithmBorder(grid, data);
        case AlgorithmType::SECTIONS:
            return new AlgorithmSections(grid, data);
        case AlgorithmType::SEGMENTS:
            return new AlgorithmSegments(grid, data);
        case AlgorithmType::SUBSEGMENTS:
            return new AlgorithmSubsegments(grid, data);
        case AlgorithmType::FACE:
            return new AlgorithmFace(grid, data);
        case AlgorithmType::COMBINATIONS:
            return new AlgorithmCombinations(grid, data);
        case AlgorithmType::SIMPLE_CORNERS:
            return new AlgorithmSimpleCorners(grid, data);
        case AlgorithmType::LAYER_ONE:
            return new AlgorithmLayerOne(grid, data);
        case AlgorithmType::LAYER_TWO:
            return new AlgorithmLayerTwo(grid, data);
        case AlgorithmType::COMBINATIONS_SAFE_MOVES:
            return new AlgorithmCombinationsSafeMoves(grid, data);
        case AlgorithmType::COMBINATIONS_LEAST_RISKY:
            return new AlgorithmCombinationsLeastRisky(grid, data);
        case AlgorithmType::GIVE_UP:
            return new AlgorithmGiveUp(grid, data);
        case AlgorithmType::FIRST_MOVE:
            return new AlgorithmFirstMove(grid, data);
        case AlgorithmType::SIMPLE_ACTIONS:
            return new AlgorithmSimpleActions(grid, data);
        default:
            LOGGER_THROW("AlgorithmFactory::Create - unhandled AlgorithmType");
    }
}