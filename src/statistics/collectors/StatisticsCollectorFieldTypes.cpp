#include "StatisticsCollectorFieldTypes.hpp"

StatisticsCollectorFieldTypes::StatisticsCollectorFieldTypes() :
    StatisticsCollector(
        StatisticsCollectorStruct({
            {Labels::Collectors::Generator::ZERO,  new StatisticsElementCounter()},
            {Labels::Collectors::Generator::ONE,   new StatisticsElementCounter()},
            {Labels::Collectors::Generator::TWO,   new StatisticsElementCounter()},
            {Labels::Collectors::Generator::THREE, new StatisticsElementCounter()},
            {Labels::Collectors::Generator::FOUR,  new StatisticsElementCounter()},
            {Labels::Collectors::Generator::FIVE,  new StatisticsElementCounter()},
            {Labels::Collectors::Generator::SIX,   new StatisticsElementCounter()},
            {Labels::Collectors::Generator::SEVEN, new StatisticsElementCounter()},
            {Labels::Collectors::Generator::EIGHT, new StatisticsElementCounter()}})),
    count_0((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::Generator::ZERO]),
    count_1((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::Generator::ONE]),
    count_2((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::Generator::TWO]),
    count_3((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::Generator::THREE]),
    count_4((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::Generator::FOUR]),
    count_5((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::Generator::FIVE]),
    count_6((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::Generator::SIX]),
    count_7((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::Generator::SEVEN]),
    count_8((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::Generator::EIGHT])
{
    count_0 = 0U;
    count_1 = 0U;
    count_2 = 0U;
    count_3 = 0U;
    count_4 = 0U;
    count_5 = 0U;
    count_6 = 0U;
    count_7 = 0U;
    count_8 = 0U;
    Enable();
}

StatisticsCollectorFieldTypes::~StatisticsCollectorFieldTypes()
{

}

void StatisticsCollectorFieldTypes::Enable()
{
    CountFieldTypesFunction = &_CountFieldTypes;
    StatisticsCollector::Enable();
}

void StatisticsCollectorFieldTypes::Disable()
{
    CountFieldTypesFunction = &_DoNothing;
    StatisticsCollector::Disable();
}


void StatisticsCollectorFieldTypes::CountFieldTypes(const std::vector<uint8_t>& field_values)
{
    CountFieldTypesFunction(*this, field_values);
}

void StatisticsCollectorFieldTypes::_CountFieldTypes(const std::vector<uint8_t>& field_values)
{
    uint64_t t0, t1, t2, t3, t4, t5, t6, t7, t8;
    t0 = t1 = t2 = t3 = t4 = t5 = t6 = t7 = t8 = 0U;
    for(const uint8_t& field : field_values)
    {
        switch (field)
        {
            case 0U:
                t0++;
                break;
            case 1U:
                t1++;
                break;
            case 2U:
                t2++;
                break;
            case 3U:
                t3++;
                break;
            case 4U:
                t4++;
                break;
            case 5U:
                t5++;
                break;
            case 6U:
                t6++;
                break;
            case 7U:
                t7++;
                break;
            case 8U:
                t8++;
                break;
            default:
                break;
        }
    }
    count_0 += t0;
    count_1 += t1;
    count_2 += t2;
    count_3 += t3;
    count_4 += t4;
    count_5 += t5;
    count_6 += t6;
    count_7 += t7;
    count_8 += t8;
}

StatisticsCollector* StatisticsCollectorFieldTypes::CreateNew() const
{
    return new StatisticsCollectorFieldTypes();
}
