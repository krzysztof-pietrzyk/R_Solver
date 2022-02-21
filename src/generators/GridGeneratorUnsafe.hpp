#ifndef GridGeneratorUnsafe_hpp
#define GridGeneratorUnsafe_hpp

#include <random>
#include <chrono>
#include <limits.h>

#include "GridInternalGenerator.hpp"

class GridGeneratorUnsafe : public GridInternalGenerator
{
    public:

    GridGeneratorUnsafe(GridSelfGenerated& grid);

    ~GridGeneratorUnsafe();

    void Generate();

    protected:

    std::minstd_rand rng;

	std::uniform_int_distribution<int> dist;
};

#endif
