#ifndef STATISTICS_ELEMENT_HPP
#define STATISTICS_ELEMENT_HPP

#include <functional>
#include <string>

class StatisticsElement
{
    public:

    StatisticsElement();
    ~StatisticsElement();

    virtual void Enable() = 0;
    virtual void Disable() = 0;
    virtual void Clear() = 0;
    virtual std::string String() = 0;

    virtual void operator+=(const StatisticsElement& other) = 0;
    virtual void operator=(const StatisticsElement& other) = 0;

    protected:

    void _DoNothing(...);
};

#endif
