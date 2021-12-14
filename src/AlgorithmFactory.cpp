#include "AlgorithmFactory.hpp"

AlgorithmFactory::AlgorithmFactory() {}

AlgorithmFactory::~AlgorithmFactory() {}

Algorithm* AlgorithmFactory::Create(AlgorithmType type, GridManager& grid)
{
    switch(type)
    {
        case ALGORITHM_LAYER_ONE:
            return new AlgorithmLayerOne(grid);
        case ALGORITHM_SIMPLE_CORNERS:
            return new AlgorithmSimpleCorners(grid);
        default:
            return NULL;
    }
}