#include "GeneratorInternal.hpp"

GeneratorInternal::GeneratorInternal(GridAccessGeneratorIf& grid_) : GeneratorImpl(grid_)
{
    LOGGER(LOG_INIT) << "GeneratorInternal";
    generated_safe_fields = std::vector<uint32_t>(grid.GetSize(), 0U);
    forced_safe_fields = std::vector<uint32_t>();
    generated_mine_fields = CachedVector(grid.GetSize());
    generated_field_values = std::vector<uint8_t>(grid.GetSize(), 0U);
    statistics_field_types = new StatisticsCollectorFieldTypes();  // deleted in StatisticsProducer
    statistics_collectors.push_back(statistics_field_types);
}

GeneratorInternal::~GeneratorInternal()
{
    
}

void GeneratorInternal::GenerateGrid()
{
    LOGGER(LOG_DEBUG) << "GeneratorInternal::GenerateGrid";
    ClearPreviousGrid();
    GenerateMinePositions();  // Pure virtual
    CalculateAllFieldValues();
    CopyGeneratedVectorsToGrid();
}

void GeneratorInternal::ClearPreviousGrid()
{
    grid.Reset();
    generated_mine_fields.Clear();
}

void GeneratorInternal::CalculateAllFieldValues()
{
    CalculateRegularFieldValues();
    CalculateForcedSafeFieldValues();
    SetValuesForMineFields();
    statistics_field_types->CountFieldTypes(generated_field_values);
}

void GeneratorInternal::CalculateRegularFieldValues()
{
    for(const uint32_t& current_field : generated_safe_fields)
    {
        generated_field_values[current_field] = CalculateFieldValue(current_field);
    }
}

void GeneratorInternal::CalculateForcedSafeFieldValues()
{
    for(const uint32_t& current_field : forced_safe_fields)
    {
        generated_field_values[current_field] = CalculateFieldValue(current_field);
    }
}

void GeneratorInternal::SetValuesForMineFields()
{
    // Different from all other fields, to avoid confusion in some cases
    const uint8_t value_for_mine_fields = 9U;
    for(const uint32_t& current_field : generated_mine_fields)
    {
        generated_field_values[current_field] = value_for_mine_fields;
    }
}

uint8_t GeneratorInternal::CalculateFieldValue(uint32_t field)
{
    uint8_t current_field_value = 0U;
    const std::vector<uint32_t>& neighbors = grid.GetNeighbors(field);
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

void GeneratorInternal::CopyGeneratedVectorsToGrid()
{
    grid.SetMineFields(generated_mine_fields);
    grid.SetFieldValues(generated_field_values);
}
