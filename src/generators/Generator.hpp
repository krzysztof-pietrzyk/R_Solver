#ifndef GENERATOR_HPP
#define GENERATOR_HPP

// project includes
#include "../statistics/StatisticsProducer.hpp"
#include "../grid/GridGeneratorIf.hpp"

// std includes

// forward declarations


class Generator : public StatisticsProducer
{
    public:

    Generator(GridGeneratorIf& grid_);

    ~Generator();

    virtual void GenerateGrid() = 0;

    virtual void SetStartingField(uint32_t new_starting_field);

    protected:

    GridGeneratorIf& grid;
    const GridDimensions grid_dim;

    uint32_t starting_field;
};

#endif
