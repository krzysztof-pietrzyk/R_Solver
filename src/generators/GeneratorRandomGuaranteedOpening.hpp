#ifndef GENERATOR_RANDOM_GUARANTEED_OPENING_HPP
#define GENERATOR_RANDOM_GUARANTEED_OPENING_HPP

// project includes
#include "GeneratorRandom.hpp"

// std includes

// forward declarations


class GeneratorRandomGuaranteedOpening : public GeneratorRandom
{
    public:

    GeneratorRandomGuaranteedOpening(GridGeneratorIf& grid_);

    ~GeneratorRandomGuaranteedOpening();

    protected:

    virtual void ValidateGridDimensions() override;

    virtual void CreateTemplate() override;

    private:

    static const uint32_t minimum_safe_fields;
};

#endif
