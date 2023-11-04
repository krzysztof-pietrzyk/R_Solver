#ifndef STATISTICS_ELEMENT_AVERAGE_HPP
#define STATISTICS_ELEMENT_AVERAGE_HPP

// project includes
#include "StatisticsElementIf.hpp"

// std includes
#include <mutex>

// forward declarations


class StatisticsElementAverage : public StatisticsElementIf
{
    public:

    StatisticsElementAverage();

    ~StatisticsElementAverage();

    virtual StatisticsElementIf* Clone() override;
    virtual std::string String() const override;
    virtual bool IsEmpty() override;

    virtual void FlushToOutput(StatisticsElementIf* output) override;

    void AddEntryToAverage(uint64_t new_value);

    private:

    uint64_t total_sum;
    uint64_t number_of_entries;
    double average;
    std::mutex mut;

    void UpdateAverage();
};

#endif
