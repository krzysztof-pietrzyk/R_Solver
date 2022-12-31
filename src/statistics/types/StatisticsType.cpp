#include "StatisticsType.hpp"

StatisticsType::StatisticsType()
{
    data_elements = StatisticsTypeLabelledStruct();
}

StatisticsType::~StatisticsType() {}

StatisticsTypeLabelledStruct StatisticsType::GetStatistics() const
{
    return StatisticsTypeLabelledStruct(data_elements);
}

void StatisticsType::operator+= (const StatisticsType& other)
{
    for(auto& item : data_elements)
    {
        const std::string& key = item.first;
        item.second += other.data_elements.at(key);
    }
}

StatisticsType* StatisticsType::Clone() const
{
    StatisticsType* clone = CreateNew();
    for(const auto& item : data_elements)
    {
        const std::string& key = item.first;
        clone->data_elements[key] = item.second;
    }
    return clone;
}

void StatisticsType::Clear()
{
    for(auto& item : data_elements)
    {
        item.second = 0U;
    }
}
