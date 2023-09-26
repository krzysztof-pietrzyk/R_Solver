#include "StatisticsAggregator.hpp"

StatisticsAggregator::StatisticsAggregator()
{
    aggregated_statistics = StatisticsAggregatorStruct();
}

StatisticsAggregator::~StatisticsAggregator()
{

}

void StatisticsAggregator::RegisterStatisticsProducer(const Label producer_label, const StatisticsProducer* statistics_producer)
{
    const StatisticsProducerStruct& statistics_collectors = statistics_producer->GetStatisticsCollectors();
    for(StatisticsCollector* statistics_collector : statistics_collectors)
    {
        aggregated_statistics[producer_label].push_back(statistics_collector);
    }
}

void StatisticsAggregator::FlushToOutput(StatisticsAggregatorStruct& output) const
{
    for(const auto& labelled_producer_struct : aggregated_statistics)
    {
        const Label& producer_key = labelled_producer_struct.first;
        const StatisticsProducerStruct& input_producer_struct = labelled_producer_struct.second;
        if(output.find(producer_key) == output.end())
        {
            // Should only happen once in the beginning
            for(const StatisticsCollector* statistics_collector : input_producer_struct)
            {
                output[producer_key].push_back(statistics_collector->Clone());
            }
        }
        StatisticsProducerStruct& output_producer_struct = output[producer_key];
        LOGGER_ASSERT(input_producer_struct.size() == output_producer_struct.size(), "StatisticsAggregator::FlushToOutput - size mismatch.");
        for(size_t i = 0; i < input_producer_struct.size(); i++)
        {
            (*input_producer_struct[i]).FlushToOutput(*(output_producer_struct[i]));
        }
    }
}
