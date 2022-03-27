#include "GridGeneratorFactory.hpp"

GridGeneratorFactory::GridGeneratorFactory() {}

GridGeneratorFactory::~GridGeneratorFactory() {}

GridInternalGenerator* GridGeneratorFactory::Create(GridGeneratorType type, GridSelfGenerated& grid)
{
    switch(type)
    {
        case GENERATOR_UNSAFE:
            return new GridGeneratorUnsafe(grid);
        case GENERATOR_SAFE:
            return new GridGeneratorSafe(grid);
        case GENERATOR_FROM_HASH:
            return new GridGeneratorFromHash(grid);
        default:
            throw std::invalid_argument("ERROR: Attempting to create a non-existent Generator type!");
    }
}
