#include "AlgorithmFactory.hpp"

Algorithm* AlgorithmFactory::Create(AlgorithmType type, GridAccessPlayerIf& grid, AlgorithmDataStorage& data)
{
    switch(type)
    {
        case REFRESH_BORDER:
            return new AlgorithmRefreshBorder(grid, data);
        case REFRESH_SECTIONS:
            return new AlgorithmRefreshSections(grid, data);
        case REFRESH_SEGMENTS:
            return new AlgorithmRefreshSegments(grid, data);
        case REFRESH_SUBSEGMENTS:
            return new AlgorithmRefreshSubsegments(grid, data);
        case REFRESH_FACE:
            return new AlgorithmRefreshFace(grid, data);
        case REFRESH_COMBINATIONS:
            return new AlgorithmRefreshCombinations(grid, data);
        case SIMPLE_CORNERS:
            return new AlgorithmSimpleCorners(grid, data);
        case LAYER_ONE:
            return new AlgorithmLayerOne(grid, data);
        case LAYER_TWO:
            return new AlgorithmLayerTwo(grid, data);
        case COMBINATIONS_SAFE_MOVES:
            return new AlgorithmCombinationsSafeMoves(grid, data);
        case COMBINATIONS_LEAST_RISKY:
            return new AlgorithmCombinationsLeastRisky(grid, data);
        case GIVE_UP:
            return new AlgorithmGiveUp(grid, data);
        case FIRST_MOVE:
            return new AlgorithmFirstMove(grid, data);
        default:
            throw std::invalid_argument("ERROR: Attempting to create a non-existent Algorithm type!");
    }
}