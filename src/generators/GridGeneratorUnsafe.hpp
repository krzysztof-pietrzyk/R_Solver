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

    virtual void SetStartingField(unsigned int starting_field);

    protected:

    virtual void PrepareSafeFields();

    virtual void CopySafeFields();

    std::minstd_rand rng;
	std::uniform_int_distribution<int> dist;
    std::vector<unsigned int> forced_safe;  // For other generators deriving from this
    unsigned int current_max;
};

#endif
