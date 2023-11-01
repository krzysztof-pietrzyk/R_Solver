#ifndef GENERATOR_RANDOM_UNSAFE_HPP
#define GENERATOR_RANDOM_UNSAFE_HPP

// project includes
#include "GeneratorRandom.hpp"

// std includes

// forward declarations


class GeneratorRandomUnsafe : public GeneratorRandom
{
    public:

    GeneratorRandomUnsafe(GridGeneratorIf& grid_);

    ~GeneratorRandomUnsafe();

    protected:

    virtual void ValidateGridDimensions() override;

    virtual void CreateTemplate() override;
};

#endif
