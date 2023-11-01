#ifndef GENERATOR_RANDOM_SAFE_HPP
#define GENERATOR_RANDOM_SAFE_HPP

// project includes
#include "GeneratorRandom.hpp"

// std includes

// forward declarations


class GeneratorRandomSafe : public GeneratorRandom
{
    public:

    GeneratorRandomSafe(GridGeneratorIf& grid_);

    ~GeneratorRandomSafe();

    protected:

    virtual void ValidateGridDimensions() override;

    virtual void CreateTemplate() override;

    private:

    static const uint32_t minimum_safe_fields;
};

#endif
