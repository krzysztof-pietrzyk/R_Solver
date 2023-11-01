#ifndef GENERATOR_FACTORY_HPP
#define GENERATOR_FACTORY_HPP

// project includes
#include "Generator.hpp"
#include "GeneratorType.hpp"

// std includes

// forward declarations
class GridGeneratorIf;


class GeneratorFactory
{
    public:

    GeneratorFactory() = delete;

    ~GeneratorFactory() = delete;

    static Generator* Create(GeneratorType type, GridGeneratorIf& grid);
};

#endif
