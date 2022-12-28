#ifndef STATISTICS_TYPE_HPP
#define STATISTICS_TYPE_HPP

#include <cstdint>

class StatisticsType
{
    public:

    StatisticsType();
    ~StatisticsType();

    virtual void CopyToOutput(StatisticsType& output_data) = 0;
};

#endif
