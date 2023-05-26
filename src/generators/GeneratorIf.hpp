#ifndef GENERATOR_IF_HPP
#define GENERATOR_IF_HPP

#include <cstdint>

class GeneratorIf
{
    public:

    virtual void GenerateGrid() = 0;

    virtual void SetStartingField(uint32_t new_starting_field) = 0;
};

#endif
