#ifndef GENERATOR_RANDOM_SAFE_HPP
#define GENERATOR_RANDOM_SAFE_HPP

#include "GeneratorRandom.hpp"

class GeneratorRandomSafe : public GeneratorRandom
{
    public:

    GeneratorRandomSafe(GridAccessGeneratorIf& grid_);

    ~GeneratorRandomSafe();

    protected:

    virtual void ValidateGridDimensions() override;

    virtual void CreateTemplate() override;
};

#endif