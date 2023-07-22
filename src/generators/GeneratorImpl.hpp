#ifndef GENERATOR_IMPL_HPP
#define GENERATOR_IMPL_HPP

#include "../grid/GridAccessGeneratorIf.hpp"
#include "../statistics/StatisticsProducer.hpp"


#include "GeneratorIf.hpp"

class GeneratorImpl :
    public GeneratorIf,
    public StatisticsProducer
{
    public:

    GeneratorImpl(GridAccessGeneratorIf& grid_);

    ~GeneratorImpl();

    virtual void SetStartingField(uint32_t new_starting_field) override;

    protected:

    GridAccessGeneratorIf& grid;

    uint32_t starting_field;
};

#endif
