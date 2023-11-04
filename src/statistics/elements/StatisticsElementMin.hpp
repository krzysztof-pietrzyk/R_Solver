#ifndef STATISTICS_ELEMENT_MIN_HPP
#define STATISTICS_ELEMENT_MIN_HPP

// project includes
#include "StatisticsElementIf.hpp"

// std includes

// forward declarations


class StatisticsElementMin : public StatisticsElementIf
{
    public:

    StatisticsElementMin();

    ~StatisticsElementMin();

    virtual StatisticsElementIf* Clone() override;
    virtual std::string String() const override;
    virtual bool IsEmpty() override;

    virtual void FlushToOutput(StatisticsElementIf* output) override;

    void CompareAndSet(uint64_t new_value);

    private:

    uint64_t element_value;
};

#endif
