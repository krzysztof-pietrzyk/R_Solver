#include "StatisticsCollector.hpp"

StatisticsCollector::StatisticsCollector(StatisticsCollectorStruct init_struct)
{
    labelled_data_elements = init_struct;
    Enable();
}

StatisticsCollector::~StatisticsCollector()
{
    for(auto& item : labelled_data_elements)
    {
        delete item.second;
    }
}

void StatisticsCollector::Enable()
{
    for(auto& item : labelled_data_elements)
    {
        item.second->Enable();
    }
}

void StatisticsCollector::Disable()
{
    for(auto& item : labelled_data_elements)
    {
        item.second->Disable();
    }
}

void StatisticsCollector::Clear()
{
    for(auto& item : labelled_data_elements)
    {
        item.second->Clear();
    }
}

const StatisticsCollectorStruct& StatisticsCollector::GetStatistics() const
{
    return labelled_data_elements;
}

StatisticsCollector* StatisticsCollector::Clone() const
{
    StatisticsCollector* clone = CreateNew();
    for(const auto& item : labelled_data_elements)
    {
        const Label& key = item.first;
        clone->labelled_data_elements[key] = item.second->Clone();
    }
    return clone;
}

void StatisticsCollector::operator+= (const StatisticsCollector& other)
{
    for(auto& item : labelled_data_elements)
    {
        const Label& key = item.first;
        *(item.second) += *(other.labelled_data_elements.at(key));
    }
}

void StatisticsCollector::operator= (const StatisticsCollector& other)
{
    for(auto& item : labelled_data_elements)
    {
        const Label& key = item.first;
        *(item.second) = *(other.labelled_data_elements.at(key));
    }
}

void StatisticsCollector::_DoNothing(...)
{
    
}
