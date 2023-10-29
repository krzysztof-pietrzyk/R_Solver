#include "StatisticsAggregator.hpp"

StatisticsAggregator::StatisticsAggregator()
{
    labelled_producers = std::map<Label, StatisticsProducer*>();
}

StatisticsAggregator::~StatisticsAggregator()
{

}

void StatisticsAggregator::RegisterStatisticsProducer(const Label producer_label, StatisticsProducer* statistics_producer)
{
    labelled_producers[producer_label] = statistics_producer;
}

StatisticsAggregator* StatisticsAggregator::Clone() const
{
    StatisticsAggregator* clone = new StatisticsAggregator();
    for(const auto& labelled_producer : labelled_producers)
    {
        const Label& producer_label = labelled_producer.first;
        const StatisticsProducer* producer = labelled_producer.second;
        clone->labelled_producers[producer_label] = producer->Clone();
    }
    return clone;
}

std::string StatisticsAggregator::String() const
{
    std::ostringstream text_to_print = std::ostringstream();
    for(const auto& labelled_producer : labelled_producers)
    {
        const Label& producer_label = labelled_producer.first;
        const StatisticsProducer* producer = labelled_producer.second;
        text_to_print << producer_label << '\n' << producer->String();
    }
    return text_to_print.str();
}

void StatisticsAggregator::FlushToOutput(StatisticsAggregator* output) const
{
    std::map<Label, StatisticsProducer*>& output_labelled_producers = output->labelled_producers;
    for(const auto& labelled_producer : labelled_producers)
    {
        const Label& producer_label = labelled_producer.first;
        const StatisticsProducer* input_producer = labelled_producer.second;
        StatisticsProducer* output_producer = output_labelled_producers[producer_label];
        input_producer->FlushToOutput(output_producer);
    }
}
