#include "GridGeneratorFactory.hpp"

GridGeneratorFactory::GridGeneratorFactory() {}

GridGeneratorFactory::~GridGeneratorFactory() {}

GridGenerator* GridGeneratorFactory::Create(GridGeneratorType type, Grid& grid)
{
    switch(type)
    {
        case GENERATOR_UNSAFE:
            return new GridGeneratorUnsafe(grid);
        case GENERATOR_FROM_HASH:
            return new GridGeneratorFromHash(grid);
        default:
            return NULL;
    }
}
