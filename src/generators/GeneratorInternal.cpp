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
    starting_field = 0U;
}

GeneratorInternal::~GeneratorInternal()
{
    
}

void GeneratorInternal::GenerateGrid()
{
    LOGGER(LogLevel::DEBUG4) << "GeneratorInternal::GenerateGrid";
    grid.Reset();
    ClearGeneratedVectors();
    GenerateMinePositions();  // Pure virtual
    CalculateFieldValues();
    CountFieldTypes(generated_field_values);
    CopyGeneratedDataToGrid();
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
    counter_double_eight = new StatisticsElementCounter();
    counter_triple_eight = new StatisticsElementCounter();
    counter_quadruple_eight = new StatisticsElementCounter();
    statistics_collector->AddElement(Labels::Elements::Generator::ZERO, counter_zero);
    statistics_collector->AddElement(Labels::Elements::Generator::ONE, counter_one);
    statistics_collector->AddElement(Labels::Elements::Generator::TWO, counter_two);
    statistics_collector->AddElement(Labels::Elements::Generator::THREE, counter_three);
    statistics_collector->AddElement(Labels::Elements::Generator::FOUR, counter_four);
    statistics_collector->AddElement(Labels::Elements::Generator::FIVE, counter_five);
    statistics_collector->AddElement(Labels::Elements::Generator::SIX, counter_six);
    statistics_collector->AddElement(Labels::Elements::Generator::SEVEN, counter_seven);
    statistics_collector->AddElement(Labels::Elements::Generator::EIGHT, counter_eight);
    statistics_collector->AddElement(Labels::Elements::Generator::EIGHT_2X, counter_double_eight);
    statistics_collector->AddElement(Labels::Elements::Generator::EIGHT_3X, counter_triple_eight);
    statistics_collector->AddElement(Labels::Elements::Generator::EIGHT_4X, counter_quadruple_eight);
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
    if(t8 >= 2)
    {
        *counter_double_eight += 1;
    }
    if(t8 >= 3)
    {
        *counter_triple_eight += 1;
    }
    if(t8 >= 4)
    {
        *counter_quadruple_eight += 1;
    }
}
