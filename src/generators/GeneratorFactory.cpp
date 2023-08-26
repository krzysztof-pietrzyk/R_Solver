#include "GeneratorFactory.hpp"

Generator* GeneratorFactory::Create(GeneratorType type, GridAccessGeneratorIf& grid)
{
    switch(type)
    {
        case GeneratorType::UNSAFE:
            return new GeneratorRandomUnsafe(grid);
        case GeneratorType::SAFE:
            return new GeneratorRandomSafe(grid);
        case GeneratorType::GUARANTEED_OPENING:
            return new GeneratorRandomGuaranteedOpening(grid);
        default:
            LOGGER_THROW("GeneratorFactory::Create - unhandled GeneratorType");
    }
}