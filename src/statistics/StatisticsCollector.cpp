#include "StatisticsCollector.hpp"

StatisticsCollector::StatisticsCollector()
{
    statistics = std::map<std::string, std::vector<StatisticsType*>>();
}

StatisticsCollector::~StatisticsCollector()
{

}

void StatisticsCollector::RegisterStatisticsProducer(const std::string producer_label, const StatisticsProducer* statistics_producer)
{
    const std::vector<StatisticsType*>& statistics_types = statistics_producer->GetStatisticsTypes();
    for(StatisticsType* type : statistics_types)
    {
        statistics[producer_label].push_back(type);
    }
}
