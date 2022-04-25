#include "AlgorithmFactory.hpp"

AlgorithmFactory::AlgorithmFactory(GridManager& grid_, AlgorithmDataStorage& data_) : grid(grid_), data(data_) {}

AlgorithmFactory::~AlgorithmFactory() {}

Algorithm* AlgorithmFactory::Create(AlgorithmType type)
{
    switch(type)
    {
        case ALGORITHM_REFRESH_BORDER:
            return new AlgorithmRefreshBorder(grid, data);
        case ALGORITHM_REFRESH_SECTIONS:
            return new AlgorithmRefreshSections(grid, data);
        case ALGORITHM_REFRESH_SEGMENTS:
            return new AlgorithmRefreshSegments(grid, data);
        case ALGORITHM_REFRESH_COMBINATIONS:
            return new AlgorithmRefreshCombinations(grid, data);
        case ALGORITHM_LAYER_ONE:
            return new AlgorithmLayerOne(grid, data);
        case ALGORITHM_LAYER_TWO:
            return new AlgorithmLayerTwo(grid, data);
        case ALGORITHM_SIMPLE_CORNERS:
            return new AlgorithmSimpleCorners(grid, data);
        default:
            throw std::invalid_argument("ERROR: Attempting to create a non-existent Algorithm type!");
    }
}