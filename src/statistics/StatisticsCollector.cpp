// implemented header
#include "StatisticsCollector.hpp"

// project includes
#include "elements/StatisticsElementIf.hpp"
#include "../utils/Label.hpp"

// std includes
#include <sstream>


StatisticsCollector::StatisticsCollector()
{
    labelled_elements = std::map<Label, StatisticsElementIf*>();
}

StatisticsCollector::~StatisticsCollector()
{
    for(auto& item : labelled_elements)
    {
        delete item.second;
    }
}

void StatisticsCollector::Clear()
{
    for(auto& item : labelled_elements)
    {
        item.second->Clear();
    }
}

void StatisticsCollector::AddElement(Label label, StatisticsElementIf* element)
{
    labelled_elements[label] = element;
}

const std::map<Label, StatisticsElementIf*>& StatisticsCollector::GetElements() const
{
    return labelled_elements;
}

StatisticsCollector* StatisticsCollector::Clone() const
{
    StatisticsCollector* clone = new StatisticsCollector();
    for(const auto& item : labelled_elements)
    {
        const Label& key = item.first;
        clone->labelled_elements[key] = item.second->Clone();
    }
    return clone;
}

std::string StatisticsCollector::String() const
{
    std::ostringstream text_to_print = std::ostringstream();
    for(const auto& item : labelled_elements)
    {
        if(item.second->IsEmpty()) { continue; }
        text_to_print << '\t' << item.first << ": " << item.second->String() << "\n";
    }
    return text_to_print.str();
}

void StatisticsCollector::FlushToOutput(StatisticsCollector* output) const
{
    for(auto& item : labelled_elements)
    {
        const Label& key = item.first;
        item.second->FlushToOutput(output->labelled_elements.at(key));
    }
}
