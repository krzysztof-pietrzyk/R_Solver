#ifndef STATISTICS_TYPE_HPP
#define STATISTICS_TYPE_HPP

#include <cstdint>
#include <string>

class StatisticsType
{
    public:

    StatisticsType();
    ~StatisticsType();

    virtual std::string GetStatistics() = 0;
};

#endif
