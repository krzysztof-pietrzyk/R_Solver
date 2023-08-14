#include "GeneratorFactory.hpp"

Generator* GeneratorFactory::Create(GeneratorType type, GridAccessGeneratorIf& grid)
{
    switch(type)
    {
        case GeneratorType::UNSAFE:
            return new GeneratorRandomUnsafe(grid);
            break;
        case GeneratorType::SAFE:
            return new GeneratorRandomSafe(grid);
            break;
        case GeneratorType::GUARANTEED_OPENING:
            return new GeneratorRandomGuaranteedOpening(grid);
            break;
        default:
            throw std::runtime_error("ERROR! GeneratorFactory::Create() unhandled GeneratorType.");
            break;
    }
}