#include "StatisticsCollectorGridFieldTypes.hpp"

StatisticsCollectorGridFieldTypes::StatisticsCollectorGridFieldTypes() :
    StatisticsCollector(
        StatisticsCollectorStruct({
            {Labels::Collectors::Grid::ZERO,  new StatisticsElementUINT64()},
            {Labels::Collectors::Grid::ONE,   new StatisticsElementUINT64()},
            {Labels::Collectors::Grid::TWO,   new StatisticsElementUINT64()},
            {Labels::Collectors::Grid::THREE, new StatisticsElementUINT64()},
            {Labels::Collectors::Grid::FOUR,  new StatisticsElementUINT64()},
            {Labels::Collectors::Grid::FIVE,  new StatisticsElementUINT64()},
            {Labels::Collectors::Grid::SIX,   new StatisticsElementUINT64()},
            {Labels::Collectors::Grid::SEVEN, new StatisticsElementUINT64()},
            {Labels::Collectors::Grid::EIGHT, new StatisticsElementUINT64()}})),
    zero_count ((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Grid::ZERO]),
    one_count  ((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Grid::ONE]),
    two_count  ((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Grid::TWO]),
    three_count((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Grid::THREE]),
    four_count ((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Grid::FOUR]),
    five_count ((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Grid::FIVE]),
    six_count  ((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Grid::SIX]),
    seven_count((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Grid::SEVEN]),
    eight_count((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Grid::EIGHT])
{
    zero_count = 0U;
    one_count = 0U;
    two_count = 0U;
    three_count = 0U;
    four_count = 0U;
    five_count = 0U;
    six_count = 0U;
    seven_count = 0U;
    eight_count = 0U;
    Enable();
}

StatisticsCollectorGridFieldTypes::~StatisticsCollectorGridFieldTypes()
{

}

void StatisticsCollectorGridFieldTypes::Enable()
{
    CountFieldTypesFunction = &_CountFieldTypes;
    StatisticsCollector::Enable();
}

void StatisticsCollectorGridFieldTypes::Disable()
{
    CountFieldTypesFunction = &_DoNothing;
    StatisticsCollector::Disable();
}


void StatisticsCollectorGridFieldTypes::CountFieldTypes(const std::vector<uint8_t>& field_values)
{
    CountFieldTypesFunction(*this, field_values);
}

void StatisticsCollectorGridFieldTypes::_CountFieldTypes(const std::vector<uint8_t>& field_values)
{
    for(const uint8_t& field : field_values)
    {
        switch (field)
        {
            case 0U:
                zero_count += 1; break;
            case 1U:
                one_count += 1; break;
            case 2U:
                two_count += 1; break;
            case 3U:
                three_count += 1; break;
            case 4U:
                four_count += 1; break;
            case 5U:
                five_count += 1; break;
            case 6U:
                six_count += 1; break;
            case 7U:
                seven_count += 1; break;
            case 8U:
                eight_count += 1; break;
            default: break;
        }
    }
}

StatisticsCollector* StatisticsCollectorGridFieldTypes::CreateNew() const
{
    return new StatisticsCollectorGridFieldTypes();
}
