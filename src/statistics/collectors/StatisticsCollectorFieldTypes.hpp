#ifndef STATISTICS_COLLECTOR_FIELD_TYPES
#define STATISTICS_COLLECTOR_FIELD_TYPES

#include "StatisticsCollector.hpp"
#include "elements/StatisticsElementUINT64.hpp"

#include <functional>

class StatisticsCollectorFieldTypes : public StatisticsCollector
{
    public:

    StatisticsCollectorFieldTypes();

    ~StatisticsCollectorFieldTypes();

    StatisticsElementUINT64& count_0;
    StatisticsElementUINT64& count_1;
    StatisticsElementUINT64& count_2;
    StatisticsElementUINT64& count_3;
    StatisticsElementUINT64& count_4;
    StatisticsElementUINT64& count_5;
    StatisticsElementUINT64& count_6;
    StatisticsElementUINT64& count_7;
    StatisticsElementUINT64& count_8;

    virtual void Enable() override;
    virtual void Disable() override;

    void CountFieldTypes(const std::vector<uint8_t>& field_values);

    protected:

    std::function<void(StatisticsCollectorFieldTypes&, const std::vector<uint8_t>&)> CountFieldTypesFunction;

    void _CountFieldTypes(const std::vector<uint8_t>& field_values);

    virtual StatisticsCollector* CreateNew() const override;
};

#endif
