#ifndef STATISTICS_TYPE_HPP
#define STATISTICS_TYPE_HPP

#include <cstdint>
#include <string>
#include <map>

class StatisticsType
{
    public:

    StatisticsType();
    ~StatisticsType();

    virtual std::map<std::string, uint64_t> GetStatistics() const = 0;

    virtual void operator+= (const StatisticsType& other) = 0;

    virtual StatisticsType* Clone() const = 0;

    virtual void Clear() = 0;
};

#endif
