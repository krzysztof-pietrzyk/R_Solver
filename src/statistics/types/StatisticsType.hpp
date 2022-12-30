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

    std::map<std::string, uint64_t> GetStatistics() const;

    void operator+= (const StatisticsType& other);

    StatisticsType* Clone() const;

    void Clear();

    std::map<std::string, uint64_t> data_elements;

    protected:

    virtual StatisticsType* CreateNew() const = 0;
};

#endif
