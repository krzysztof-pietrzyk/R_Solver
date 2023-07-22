#include "StatisticsCollectorFieldTypes.hpp"

StatisticsCollectorFieldTypes::StatisticsCollectorFieldTypes() :
    StatisticsCollector(
        StatisticsCollectorStruct({
            {Labels::Collectors::Generator::ZERO,  new StatisticsElementUINT64()},
            {Labels::Collectors::Generator::ONE,   new StatisticsElementUINT64()},
            {Labels::Collectors::Generator::TWO,   new StatisticsElementUINT64()},
            {Labels::Collectors::Generator::THREE, new StatisticsElementUINT64()},
            {Labels::Collectors::Generator::FOUR,  new StatisticsElementUINT64()},
            {Labels::Collectors::Generator::FIVE,  new StatisticsElementUINT64()},
            {Labels::Collectors::Generator::SIX,   new StatisticsElementUINT64()},
            {Labels::Collectors::Generator::SEVEN, new StatisticsElementUINT64()},
            {Labels::Collectors::Generator::EIGHT, new StatisticsElementUINT64()}})),
    count_0((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Generator::ZERO]),
    count_1((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Generator::ONE]),
    count_2((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Generator::TWO]),
    count_3((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Generator::THREE]),
    count_4((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Generator::FOUR]),
    count_5((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Generator::FIVE]),
    count_6((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Generator::SIX]),
    count_7((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Generator::SEVEN]),
    count_8((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Generator::EIGHT])
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
    for(const uint8_t& field : field_values)
    {
        switch (field)
        {
            case 0U:
                count_0 += 1;
                break;
            case 1U:
                count_1 += 1;
                break;
            case 2U:
                count_2 += 1;
                break;
            case 3U:
                count_3 += 1;
                break;
            case 4U:
                count_4 += 1;
                break;
            case 5U:
                count_5 += 1;
                break;
            case 6U:
                count_6 += 1;
                break;
            case 7U:
                count_7 += 1;
                break;
            case 8U:
                count_8 += 1;
                break;
            default:
                break;
        }
    }
}

StatisticsCollector* StatisticsCollectorFieldTypes::CreateNew() const
{
    return new StatisticsCollectorFieldTypes();
}
