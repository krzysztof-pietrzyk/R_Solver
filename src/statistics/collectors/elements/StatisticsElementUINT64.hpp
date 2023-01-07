#ifndef STATISTICS_ELEMENT_UINT64_HPP
#define STATISTICS_ELEMENT_UINT64_HPP

#include "StatisticsElement.hpp"

#include <cstdint>

class StatisticsElementUINT64 : public StatisticsElement
{
    public:

    StatisticsElementUINT64();
    StatisticsElementUINT64(const StatisticsElementUINT64& other);
    ~StatisticsElementUINT64();

    virtual void Enable() override;
    virtual void Disable() override;
    virtual void Clear() override;
    virtual std::string String() override;

    virtual void operator+=(const StatisticsElement& other) override;
    virtual void operator=(const StatisticsElement& other) override;

    void operator+=(const uint64_t& other);
    void operator=(const uint64_t& other);

    protected:

    uint64_t element_value;

    std::function<void(StatisticsElementUINT64&, const uint64_t&)> InPlaceAddFunction;
    std::function<void(StatisticsElementUINT64&, const uint64_t&)> AssignFunction;

    void _InPlaceAdd(const uint64_t& other);
    void _Assign(const uint64_t& other);
};

#endif
