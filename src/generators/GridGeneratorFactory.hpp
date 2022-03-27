#ifndef GridGeneratorFactory_hpp
#define GridGeneratorFactory_hpp

#include <stdexcept>

#include "GridInternalGenerator.hpp"
#include "GridGeneratorUnsafe.hpp"
#include "GridGeneratorSafe.hpp"
#include "GridGeneratorFromHash.hpp"

enum GridGeneratorType
{
    GENERATOR_UNSAFE,
    GENERATOR_SAFE,
    GENERATOR_FROM_HASH
};

class GridGeneratorFactory
{
    public:

    static GridInternalGenerator* Create(GridGeneratorType type, GridSelfGenerated& grid);

    ~GridGeneratorFactory();

    protected:

    GridGeneratorFactory();

};

#endif