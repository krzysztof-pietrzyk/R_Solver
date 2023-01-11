#ifndef STATISTICS_COLLECTOR_GRID_FIELD_TYPES
#define STATISTICS_COLLECTOR_GRID_FIELD_TYPES

#include "StatisticsCollector.hpp"
#include "elements/StatisticsElementUINT64.hpp"

#include <functional>

class StatisticsCollectorGridFieldTypes : public StatisticsCollector
{
    public:

    StatisticsCollectorGridFieldTypes();

    ~StatisticsCollectorGridFieldTypes();

    StatisticsElementUINT64& zero_count;
    StatisticsElementUINT64& one_count;
    StatisticsElementUINT64& two_count;
    StatisticsElementUINT64& three_count;
    StatisticsElementUINT64& four_count;
    StatisticsElementUINT64& five_count;
    StatisticsElementUINT64& six_count;
    StatisticsElementUINT64& seven_count;
    StatisticsElementUINT64& eight_count;

    virtual void Enable() override;
    virtual void Disable() override;

    void CountFieldTypes(const std::vector<uint8_t>& field_values);

    protected:

    std::function<void(StatisticsCollectorGridFieldTypes&, const std::vector<uint8_t>&)> CountFieldTypesFunction;

    void _CountFieldTypes(const std::vector<uint8_t>& field_values);

    virtual StatisticsCollector* CreateNew() const override;
};

#endif
