#ifndef GENERATOR_COMMON_HPP
#define GENERATOR_COMMON_HPP

#include "../grid/GridAccessGeneratorIf.hpp"

#include "GeneratorIf.hpp"

class GeneratorCommon : public GeneratorIf
{
    public:

    GeneratorCommon(GridAccessGeneratorIf& grid_);

    ~GeneratorCommon();

    virtual void SetStartingField(uint32_t new_starting_field) override;

    protected:

    GridAccessGeneratorIf& grid;

    uint32_t starting_field;
};

#endif
