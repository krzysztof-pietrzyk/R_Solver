#ifndef GENERATOR_INTERNAL_HPP
#define GENERATOR_INTERNAL_HPP

#include <vector>

#include "../utils/CachedVector.hpp"

#include "GeneratorCommon.hpp"

class GeneratorInternal : public GeneratorCommon
{
    public:

    GeneratorInternal(GridAccessGeneratorIf& grid_);

    ~GeneratorInternal();

    virtual void GenerateGrid() override final;

    protected:

    std::vector<uint32_t> empty_template;
    std::vector<uint32_t> generated_safe_fields;
    CachedVector generated_mine_fields;
    std::vector<uint8_t> generated_field_values;

    virtual void GenerateMinePositions() = 0;

    virtual void CreateEmptyTemplate();

    private:

    void CalculateAllFieldValues();
    uint8_t CalculateFieldValue(uint32_t field);
    void SetValuesForMineFields();
    void ClearPreviousGrid();
    void CopyGeneratedVectorsToGrid();
};

#endif
