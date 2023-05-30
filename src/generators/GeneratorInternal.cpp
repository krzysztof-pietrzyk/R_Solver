#include "GeneratorInternal.hpp"

GeneratorInternal::GeneratorInternal(GridAccessGeneratorIf& grid_) : GeneratorCommon(grid_)
{
    generated_safe_fields = std::vector<uint32_t>(grid.GetSize(), 0U);
    generated_mine_fields = CachedVector(grid.GetTotalMines());
    generated_field_values = std::vector<uint8_t>(grid.GetSize(), 0U);
}

GeneratorInternal::~GeneratorInternal()
{
    
}

void GeneratorInternal::GenerateGrid()
{
    ClearPreviousGrid();
    GenerateMinePositions();
    CalculateAllFieldValues();
    CopyGeneratedVectorsToGrid();
}

void GeneratorInternal::CalculateAllFieldValues()
{
    // Only iterate over non-mine fields
    for(const uint32_t& current_field : generated_safe_fields)
    {
        generated_field_values[current_field] = CalculateFieldValue(current_field);
    }
    SetValuesForMineFields();
}

uint8_t GeneratorInternal::CalculateFieldValue(uint32_t field)
{
    uint8_t current_field_value = 0U;
    const std::vector<uint32_t>& neighbors = grid.GetFieldNeighbors(field);
    for(const uint32_t& current_neighbor : neighbors)
    {
        // Count how many mines are within each field's neighbors
        if(generated_mine_fields.Contains(current_neighbor))
        {
            current_field_value++;
        }
    }
    return current_field_value;
}

void GeneratorInternal::SetValuesForMineFields()
{
    const uint8_t value_for_mine_fields = 9U;  // Different from all other fields, to avoid confusion in some cases
    for(const uint32_t& current_field : generated_mine_fields)
    {
        generated_field_values[current_field] = value_for_mine_fields;
    }
}

void GeneratorInternal::ClearPreviousGrid()
{
    grid.Reset();
    generated_mine_fields.Clear();
}

void GeneratorInternal::CopyGeneratedVectorsToGrid()
{
    grid.SetMineFields(generated_mine_fields);
    grid.SetFieldValues(generated_field_values);
}
