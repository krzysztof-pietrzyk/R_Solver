#include "StatisticsCollector.hpp"

StatisticsCollector::StatisticsCollector()
{
    statistics = nullptr;
}

StatisticsCollector::StatisticsCollector(StatisticsType* statistics_type)
{
    SetStatisticsType(statistics_type);
}

StatisticsCollector::~StatisticsCollector()
{
    if(statistics != nullptr)
    {
        delete statistics;
    }
}

void StatisticsCollector::SetStatisticsType(StatisticsType* statistics_type)
{
    if(statistics != nullptr)
    {
        delete statistics;
    }
    statistics = statistics_type;
}

void StatisticsCollector::Get(StatisticsType& output_data)
{
    statistics->CopyToOutput(output_data);
}
