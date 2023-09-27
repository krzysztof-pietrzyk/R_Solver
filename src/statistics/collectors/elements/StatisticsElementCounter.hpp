#ifndef STATISTICS_ELEMENT_COUNTER_HPP
#define STATISTICS_ELEMENT_COUNTER_HPP

#include "StatisticsElement.hpp"

#include <cstdint>

class StatisticsElementCounter : public StatisticsElement
{
    public:

    StatisticsElementCounter();
    StatisticsElementCounter(const StatisticsElementCounter& other);
    ~StatisticsElementCounter();

    virtual void Enable() override;
    virtual void Disable() override;
    virtual void Clear() override;
    virtual StatisticsElement* Clone() override;
    virtual std::string String() override;

    virtual void FlushToOutput(StatisticsElement& output) override;
    virtual void operator=(const StatisticsElement& other) override;
    virtual void operator+=(const StatisticsElement& other) override;

    void operator+=(const uint64_t& other);
    void operator=(const uint64_t& other);

    protected:

    uint64_t element_value;
    uint64_t last_read_value;

    std::function<void(StatisticsElementCounter&, const uint64_t&)> InPlaceAddFunction;
    std::function<void(StatisticsElementCounter&, const uint64_t&)> AssignFunction;

    void _InPlaceAdd(const uint64_t& other);
    void _Assign(const uint64_t& other);
};

#endif
