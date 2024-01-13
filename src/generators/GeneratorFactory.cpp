// implemented header
#include "GeneratorFactory.hpp"

// project includes
#include "GeneratorLoadState.hpp"
#include "GeneratorRandomGuaranteedOpening.hpp"
#include "GeneratorRandomSafe.hpp"
#include "GeneratorRandomUnsafe.hpp"
#include "GeneratorType.hpp"

// std includes


Generator* GeneratorFactory::Create(GeneratorType type, GridGeneratorIf& grid)
{
    switch(type)
    {
        case GeneratorType::UNSAFE:
            return new GeneratorRandomUnsafe(grid);
        case GeneratorType::SAFE:
            return new GeneratorRandomSafe(grid);
        case GeneratorType::GUARANTEED_OPENING:
            return new GeneratorRandomGuaranteedOpening(grid);
        case GeneratorType::LOAD_STATE:
            return new GeneratorLoadState(grid);
        default:
            LOGGER_THROW("GeneratorFactory::Create - unhandled GeneratorType");
    }
}
