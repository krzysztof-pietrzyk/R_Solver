#ifndef STATISTICS_TYPE_HPP
#define STATISTICS_TYPE_HPP

#include "../StatisticsLabels.hpp"

#include <cstdint>
#include <string>
#include <map>
#include <vector>

class StatisticsType;
typedef std::map<std::string, uint64_t> StatisticsTypeLabelledStruct;
typedef std::vector<StatisticsType*> StatisticsProducerStruct;
typedef std::map<std::string, StatisticsProducerStruct> StatisticsCollectorLabelledStruct;

class StatisticsType
{
    public:

    StatisticsType();
    ~StatisticsType();

    StatisticsTypeLabelledStruct GetStatistics() const;

    void operator+= (const StatisticsType& other);

    StatisticsType* Clone() const;

    void Clear();

    StatisticsTypeLabelledStruct data_elements;

    protected:

    virtual StatisticsType* CreateNew() const = 0;
};

#endif
