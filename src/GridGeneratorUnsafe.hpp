#ifndef GridGeneratorUnsafe_hpp
#define GridGeneratorUnsafe_hpp

#include <random>
#include <chrono>
#include <limits.h>

#include "GridGenerator.hpp"

class GridGeneratorUnsafe : public GridGenerator
{
    public:

    GridGeneratorUnsafe(Grid& grid);

    ~GridGeneratorUnsafe();

    void Generate();

    protected:

    std::minstd_rand rng;

	std::uniform_int_distribution<int> dist;
};

#endif
