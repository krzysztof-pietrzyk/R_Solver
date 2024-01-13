// implemented header
#include "StatisticsAggregator.hpp"

// project includes
#include "StatisticsCollector.hpp"
#include "../utils/Label.hpp"

// std includes
#include <sstream>


StatisticsAggregator::StatisticsAggregator()
{
    labelled_collectors = std::map<Label, const StatisticsCollector*>();
}

StatisticsAggregator::~StatisticsAggregator()
{

}

void StatisticsAggregator::RegisterStatisticsCollector(Label collector_label, const StatisticsCollector* statistics_collector)
{
    labelled_collectors[collector_label] = statistics_collector;
}

StatisticsAggregator* StatisticsAggregator::GetNewInstance() const
{
    StatisticsAggregator* clone = new StatisticsAggregator();
    for(const auto& labelled_collector : labelled_collectors)
    {
        const Label& collector_label = labelled_collector.first;
        const StatisticsCollector* collector = labelled_collector.second;
        clone->labelled_collectors[collector_label] = collector->GetNewInstance();
    }
    return clone;
}

std::string StatisticsAggregator::String() const
{
    std::ostringstream text_to_print = std::ostringstream();
    for(const auto& labelled_collector : labelled_collectors)
    {
        const Label& collector_label = labelled_collector.first;
        const StatisticsCollector* collector = labelled_collector.second;
        text_to_print << collector_label << '\n' << collector->String();
    }
    return text_to_print.str();
}

void StatisticsAggregator::FlushToOutput(StatisticsAggregator* output) const
{
    std::map<Label, const StatisticsCollector*>& output_labelled_collectors = output->labelled_collectors;
    for(const auto& labelled_collector : labelled_collectors)
    {
        const Label& collector_label = labelled_collector.first;
        const StatisticsCollector* input_collector = labelled_collector.second;
        const StatisticsCollector* output_collector = output_labelled_collectors[collector_label];
        input_collector->FlushToOutput(output_collector);
    }
}
