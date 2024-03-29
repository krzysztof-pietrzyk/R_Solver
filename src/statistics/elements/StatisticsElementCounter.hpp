#ifndef STATISTICS_ELEMENT_COUNTER_HPP
#define STATISTICS_ELEMENT_COUNTER_HPP

// project includes
#include "StatisticsElementIf.hpp"

// std includes

// forward declarations


class StatisticsElementCounter : public StatisticsElementIf
{
    public:

    StatisticsElementCounter();
    ~StatisticsElementCounter();

    virtual StatisticsElementIf* GetNewInstance() override;
    virtual std::string String() const override;
    virtual bool IsEmpty() override;

    virtual void FlushToOutput(StatisticsElementIf* output) override;

    void operator+=(const uint64_t other);
    void operator=(const uint64_t other);

    private:

    uint64_t element_value;
    uint64_t last_read_value;
};

#endif
