#ifndef STATISTICS_ELEMENT_IF_HPP
#define STATISTICS_ELEMENT_IF_HPP

// project includes

// std includes
#include <string>

// forward declarations


class StatisticsElementIf
{
    public:

    virtual StatisticsElementIf* Clone() = 0;
    virtual std::string String() const = 0;
    virtual bool IsEmpty() = 0;

    virtual void FlushToOutput(StatisticsElementIf* output) = 0;
};

#endif
