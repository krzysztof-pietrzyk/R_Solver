#ifndef STATISTICS_ELEMENT_COUNTER_HPP
#define STATISTICS_ELEMENT_COUNTER_HPP

#include "StatisticsElementIf.hpp"

#include <cstdint>

class StatisticsElementCounter : public StatisticsElementIf
{
    public:

    StatisticsElementCounter();
    ~StatisticsElementCounter();

    virtual void Clear() override;
    virtual StatisticsElementIf* Clone() override;
    virtual std::string String() const override;
    virtual bool IsEmpty() override;

    virtual void FlushToOutput(StatisticsElementIf* output) override;
    virtual void operator=(const StatisticsElementIf* other) override;
    virtual void operator+=(const StatisticsElementIf* other) override;

    void operator+=(const uint64_t other);
    void operator=(const uint64_t other);

    private:

    uint64_t element_value;
    uint64_t last_read_value;
};

#endif
