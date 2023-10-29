#ifndef GENERATOR_INTERNAL_HPP
#define GENERATOR_INTERNAL_HPP

#include "../utils/CachedVector.hpp"
#include "../statistics/elements/StatisticsElementCounter.hpp"

#include "Generator.hpp"

#include <vector>

class GeneratorInternal : public Generator
{
    public:

    GeneratorInternal(GridGeneratorIf& grid_);

    ~GeneratorInternal();

    virtual void GenerateGrid() override final;

    protected:

    std::vector<uint32_t> generated_safe_fields;
    std::vector<uint32_t> forced_safe_fields;
    CachedVector generated_mine_fields;
    std::vector<uint8_t> generated_field_values;

    virtual void GenerateMinePositions() = 0;

    virtual void CalculateRegularFieldValues();

    virtual void CalculateForcedSafeFieldValues();

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

    void CalculateAllFieldValues();

    uint8_t CalculateFieldValue(uint32_t field);

    void SetValuesForMineFields();

    void ClearPreviousGrid();

    void CopyGeneratedVectorsToGrid();

    void CountFieldTypes(const std::vector<uint8_t>& field_values);
};

#endif
