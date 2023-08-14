#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "../grid/GridAccessGeneratorIf.hpp"
#include "../statistics/StatisticsProducer.hpp"

class Generator : public StatisticsProducer
{
    public:

    Generator(GridAccessGeneratorIf& grid_);

    ~Generator();

    virtual void GenerateGrid() = 0;

    virtual void SetStartingField(uint32_t new_starting_field);

    protected:

    GridAccessGeneratorIf& grid;

    uint32_t starting_field;
};

#endif
