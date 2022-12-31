#ifndef STATISTICS_COLLECTOR_HPP
#define STATISTICS_COLLECTOR_HPP

#include "types/StatisticsType.hpp"
#include "StatisticsProducer.hpp"

#include <map>
#include <vector>
#include <string>

class StatisticsCollector
{
    public:

    StatisticsCollector();

    ~StatisticsCollector();

    void RegisterStatisticsProducer(const std::string producer_label, const StatisticsProducer* statistics_producer);

    void CopyCurrentDataToOutput(StatisticsCollectorLabelledStruct& output) const;

    protected:

    StatisticsCollectorLabelledStruct statistics;
};

#endif
