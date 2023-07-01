#ifndef GENERATOR_FACTORY_HPP
#define GENERATOR_FACTORY_HPP

#include "GeneratorRandomGuaranteedOpening.hpp"
#include "GeneratorRandomSafe.hpp"
#include "GeneratorRandomUnsafe.hpp"

enum GeneratorType
{
    UNHANDLED_TYPE,
    UNSAFE,
    SAFE,
    GUARANTEED_OPENING,
};

class GeneratorFactory
{
    public:

    GeneratorFactory() = delete;

    ~GeneratorFactory() = delete;

    static GeneratorIf* Create(GeneratorType type, GridAccessGeneratorIf& grid);
};

#endif
