// implemented header
#include "GeneratorInternal.hpp"

// project includes
#include "../statistics/StatisticsCollector.hpp"
#include "../statistics/StatisticsLabels.hpp"
#include "../statistics/elements/StatisticsElementCounter.hpp"

// std includes


GeneratorInternal::GeneratorInternal(GridGeneratorIf& grid_) : Generator(grid_)
{
    LOGGER(LogLevel::INIT) << "GeneratorInternal";
    CreateStatisticsElements();
    generated_safe_fields = std::vector<uint32_t>(grid_dim.size, 0U);
    forced_safe_fields = std::vector<uint32_t>();
    generated_mine_fields = CachedVector(grid_dim.size);
    generated_field_values = std::vector<uint8_t>(grid_dim.size, 0U);
}

GeneratorInternal::~GeneratorInternal()
{
    
}

void GeneratorInternal::GenerateGrid()
{
    LOGGER(LogLevel::DEBUG4) << "GeneratorInternal::GenerateGrid";
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

void GeneratorInternal::CreateStatisticsElements()
{
    counter_zero = new StatisticsElementCounter();
    counter_one = new StatisticsElementCounter();
    counter_two = new StatisticsElementCounter();
    counter_three = new StatisticsElementCounter();
    counter_four = new StatisticsElementCounter();
    counter_five = new StatisticsElementCounter();
    counter_six = new StatisticsElementCounter();
    counter_seven = new StatisticsElementCounter();
    counter_eight = new StatisticsElementCounter();
    statistics_collector->AddElement(Labels::Elements::Generator::ZERO, counter_zero);
    statistics_collector->AddElement(Labels::Elements::Generator::ONE, counter_one);
    statistics_collector->AddElement(Labels::Elements::Generator::TWO, counter_two);
    statistics_collector->AddElement(Labels::Elements::Generator::THREE, counter_three);
    statistics_collector->AddElement(Labels::Elements::Generator::FOUR, counter_four);
    statistics_collector->AddElement(Labels::Elements::Generator::FIVE, counter_five);
    statistics_collector->AddElement(Labels::Elements::Generator::SIX, counter_six);
    statistics_collector->AddElement(Labels::Elements::Generator::SEVEN, counter_seven);
    statistics_collector->AddElement(Labels::Elements::Generator::EIGHT, counter_eight);
}

void GeneratorInternal::CalculateAllFieldValues()
{
    CalculateRegularFieldValues();
    CalculateForcedSafeFieldValues();
    SetValuesForMineFields();
    CountFieldTypes(generated_field_values);
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
            ++current_field_value;
        }
    }
    return current_field_value;
}

void GeneratorInternal::CopyGeneratedVectorsToGrid()
{
    grid.SetMineFields(generated_mine_fields);
    grid.SetFieldValues(generated_field_values);
}

void GeneratorInternal::CountFieldTypes(const std::vector<uint8_t>& field_values)
{
    uint64_t t0, t1, t2, t3, t4, t5, t6, t7, t8;
    t0 = t1 = t2 = t3 = t4 = t5 = t6 = t7 = t8 = 0U;
    for(const uint8_t& field : field_values)
    {
        switch (field)
        {
            case 0U:
                ++t0;
                break;
            case 1U:
                ++t1;
                break;
            case 2U:
                ++t2;
                break;
            case 3U:
                ++t3;
                break;
            case 4U:
                ++t4;
                break;
            case 5U:
                ++t5;
                break;
            case 6U:
                ++t6;
                break;
            case 7U:
                ++t7;
                break;
            case 8U:
                ++t8;
                break;
            default:
                break;
        }
    }
    *counter_zero += t0;
    *counter_one += t1;
    *counter_two += t2;
    *counter_three += t3;
    *counter_four += t4;
    *counter_five += t5;
    *counter_six += t6;
    *counter_seven += t7;
    *counter_eight += t8;
}
