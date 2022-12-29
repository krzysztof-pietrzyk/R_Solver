#ifndef STATISTICS_PRODUCER_HPP
#define STATISTICS_PRODUCER_HPP

#include "types/StatisticsType.hpp"

#include <vector>

class StatisticsProducer
{
    public:

    StatisticsProducer();

    ~StatisticsProducer();

    const std::vector<StatisticsType*>& GetStatisticsTypes() const;

    protected:

    std::vector<StatisticsType*> statistics_types;

};

#endif

