#ifndef GENERATOR_INTERNAL_HPP
#define GENERATOR_INTERNAL_HPP

#include "../utils/CachedVector.hpp"
#include "../statistics/collectors/StatisticsCollectorFieldTypes.hpp"

#include "GeneratorImpl.hpp"

#include <vector>

class GeneratorInternal : public GeneratorImpl
{
    public:

    GeneratorInternal(GridAccessGeneratorIf& grid_);

    ~GeneratorInternal();

    virtual void GenerateGrid() override final;

    protected:

    std::vector<uint32_t> generated_safe_fields;
    std::vector<uint32_t> forced_safe_fields;
    CachedVector generated_mine_fields;
    std::vector<uint8_t> generated_field_values;
    StatisticsCollectorFieldTypes* statistics_field_types;

    virtual void GenerateMinePositions() = 0;

    virtual void CalculateRegularFieldValues();

    virtual void CalculateForcedSafeFieldValues();

    private:

    void CalculateAllFieldValues();

    uint8_t CalculateFieldValue(uint32_t field);

    void SetValuesForMineFields();

    void ClearPreviousGrid();

    void CopyGeneratedVectorsToGrid();
};

#endif
