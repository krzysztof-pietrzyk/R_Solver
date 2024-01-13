#ifndef STATISTICS_ELEMENT_MAX_HPP
#define STATISTICS_ELEMENT_MAX_HPP

// project includes
#include "StatisticsElementIf.hpp"

// std includes

// forward declarations


class StatisticsElementMax : public StatisticsElementIf
{
    public:

    StatisticsElementMax();

    ~StatisticsElementMax();

    virtual StatisticsElementIf* GetNewInstance() override;
    virtual std::string String() const override;
    virtual bool IsEmpty() override;

    virtual void FlushToOutput(StatisticsElementIf* output) override;

    void CompareAndSet(uint64_t new_value);

    private:

    uint64_t element_value;
};

#endif
