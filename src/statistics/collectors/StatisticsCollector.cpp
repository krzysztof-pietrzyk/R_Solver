#include "StatisticsCollector.hpp"

StatisticsCollector::StatisticsCollector()
{
    labelled_data_elements = StatisticsCollectorStruct();
}

StatisticsCollector::~StatisticsCollector() {}

const StatisticsCollectorStruct& StatisticsCollector::GetStatistics() const
{
    return labelled_data_elements;
}

void StatisticsCollector::operator+= (const StatisticsCollector& other)
{
    for(auto& item : labelled_data_elements)
    {
        const Label& key = item.first;
        item.second += other.labelled_data_elements.at(key);
    }
}

StatisticsCollector* StatisticsCollector::Clone() const
{
    StatisticsCollector* clone = CreateNew();
    for(const auto& item : labelled_data_elements)
    {
        const Label& key = item.first;
        clone->labelled_data_elements[key] = item.second;
    }
    return clone;
}

void StatisticsCollector::Clear()
{
    for(auto& item : labelled_data_elements)
    {
        item.second = 0U;
    }
}
