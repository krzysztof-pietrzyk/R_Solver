#ifndef GENERATOR_FACTORY_HPP
#define GENERATOR_FACTORY_HPP

#include "GeneratorType.hpp"
#include "GeneratorRandomGuaranteedOpening.hpp"
#include "GeneratorRandomSafe.hpp"
#include "GeneratorRandomUnsafe.hpp"

class GeneratorFactory
{
    public:

    GeneratorFactory() = delete;

    ~GeneratorFactory() = delete;

    static GeneratorImpl* Create(GeneratorType type, GridAccessGeneratorIf& grid);
};

#endif
