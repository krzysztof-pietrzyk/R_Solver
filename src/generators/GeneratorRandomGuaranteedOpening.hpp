#ifndef GENERATOR_RANDOM_GUARANTEED_OPENING_HPP
#define GENERATOR_RANDOM_GUARANTEED_OPENING_HPP

#include "GeneratorRandom.hpp"

class GeneratorRandomGuaranteedOpening : public GeneratorRandom
{
    public:

    GeneratorRandomGuaranteedOpening(GridAccessGeneratorIf& grid_);

    ~GeneratorRandomGuaranteedOpening();

    protected:

    virtual void ValidateGridDimensions() override;

    virtual void CreateTemplate() override;
};

#endif
