#ifndef GENERATOR_INTERNAL_HPP
#define GENERATOR_INTERNAL_HPP

// project includes
#include "Generator.hpp"
#include "../utils/Logger.hpp"

// std includes
#include "../utils/CachedVector.hpp"

// forward declarations
class StatisticsElementCounter;


class GeneratorInternal : public Generator
{
    public:

    GeneratorInternal(GridGeneratorIf& grid_);

    ~GeneratorInternal();

    virtual void GenerateGrid() override final;

    virtual void SetStartingField(uint32_t new_starting_field) = 0;

    protected:

    uint32_t starting_field;
    std::vector<uint32_t> forced_safe_fields;
    std::vector<uint32_t> generated_safe_fields;

    virtual void GenerateMinePositions() = 0;

    private:

    StatisticsElementCounter* counter_zero;
    StatisticsElementCounter* counter_one;
    StatisticsElementCounter* counter_two;
    StatisticsElementCounter* counter_three;
    StatisticsElementCounter* counter_four;
    StatisticsElementCounter* counter_five;
    StatisticsElementCounter* counter_six;
    StatisticsElementCounter* counter_seven;
    StatisticsElementCounter* counter_eight;

    void CreateStatisticsElements();

    void CountFieldTypes(const std::vector<uint8_t>& field_values);
};

#endif
