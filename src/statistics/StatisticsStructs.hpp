#ifndef STATISTICS_STRUCTS_HPP
#define STATISTICS_STRUCTS_HPP

#include "../utils/Label.hpp"

#include "collectors/elements/StatisticsElement.hpp"

#include <map>
#include <vector>

class StatisticsCollector;
typedef std::map<Label, StatisticsElement*> StatisticsCollectorStruct;
typedef std::vector<StatisticsCollector*> StatisticsProducerStruct;
typedef std::map<Label, StatisticsProducerStruct> StatisticsAggregatorStruct;

#endif
