#ifndef GRID_GENERATOR_UNSAFE_HPP
#define GRID_GENERATOR_UNSAFE_HPP

#include <random>
#include <chrono>
#include <limits.h>

#include "GridInternalGenerator.hpp"

class GridGeneratorUnsafe : public GridInternalGenerator
{
    public:

    GridGeneratorUnsafe(GridSelfGenerated& grid);

    ~GridGeneratorUnsafe();

    void Generate() override;

    virtual void SetStartingField(uint32_t starting_field);

    protected:

    virtual void PrepareSafeFields();

    virtual void CopySafeFields();

    std::minstd_rand rng;
	std::uniform_int_distribution<int> dist;
    std::vector<uint32_t> forced_safe;  // For other generators deriving from this
    uint32_t current_max;
};

#endif
