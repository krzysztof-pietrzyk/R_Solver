#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "../grid/GridGeneratorIf.hpp"
#include "../statistics/StatisticsProducer.hpp"

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
