#include "StatisticsCollector.hpp"

StatisticsCollector::StatisticsCollector()
{
    statistics = StatisticsCollectorLabelledStruct();
}

StatisticsCollector::~StatisticsCollector()
{

}

void StatisticsCollector::RegisterStatisticsProducer(const std::string producer_label, const StatisticsProducer* statistics_producer)
{
    const StatisticsProducerStruct statistics_types = statistics_producer->GetStatisticsTypes();
    for(StatisticsType* type : statistics_types)
    {
        statistics[producer_label].push_back(type);
    }
}

void StatisticsCollector::CopyCurrentDataToOutput(StatisticsCollectorLabelledStruct& output) const
{
    for(const auto& item : statistics)
    {
        const std::string& key = item.first;
        const StatisticsProducerStruct& input_vector = item.second;
        if(output.find(key) != output.end())
        {
            StatisticsProducerStruct& output_vector = output[key];
            if(input_vector.size() != output_vector.size())
            {
                // throw?
            }
            for(size_t i = 0; i < input_vector.size(); i++)
            {
                *(output_vector[i]) += *(input_vector[i]);
            }
        }
        else
        {
            for(const StatisticsType* s : input_vector)
            {
                output[key].push_back(s->Clone());
            }
        }
        for(StatisticsType* s : input_vector)
        {
            s->Clear();
        }
    }
}
