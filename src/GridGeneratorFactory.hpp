#ifndef GridGeneratorFactory_hpp
#define GridGeneratorFactory_hpp

#include "GridGenerator.hpp"
#include "GridGeneratorUnsafe.hpp"
#include "GridGeneratorFromHash.hpp"

enum GridGeneratorType
{
    GENERATOR_UNSAFE,
    GENERATOR_FROM_HASH
};

class GridGeneratorFactory
{
    public:

    static GridGenerator* Create(GridGeneratorType type, Grid& grid);

    ~GridGeneratorFactory();

    protected:

    GridGeneratorFactory();

};

#endif