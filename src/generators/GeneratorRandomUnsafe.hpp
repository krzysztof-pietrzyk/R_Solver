#ifndef GENERATOR_RANDOM_UNSAFE_HPP
#define GENERATOR_RANDOM_UNSAFE_HPP

#include "GeneratorRandom.hpp"

class GeneratorRandomUnsafe : public GeneratorRandom
{
    public:

    GeneratorRandomUnsafe(GridAccessGeneratorIf& grid_);

    ~GeneratorRandomUnsafe();

    protected:

    virtual void ValidateGridDimensions() override;

    virtual void CreateTemplate() override;
};

#endif
