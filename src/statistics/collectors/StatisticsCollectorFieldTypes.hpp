#ifndef STATISTICS_COLLECTOR_FIELD_TYPES
#define STATISTICS_COLLECTOR_FIELD_TYPES

#include "StatisticsCollector.hpp"
#include "elements/StatisticsElementCounter.hpp"

#include <functional>

class StatisticsCollectorFieldTypes : public StatisticsCollector
{
    public:

    StatisticsCollectorFieldTypes();

    ~StatisticsCollectorFieldTypes();

    StatisticsElementCounter& count_0;
    StatisticsElementCounter& count_1;
    StatisticsElementCounter& count_2;
    StatisticsElementCounter& count_3;
    StatisticsElementCounter& count_4;
    StatisticsElementCounter& count_5;
    StatisticsElementCounter& count_6;
    StatisticsElementCounter& count_7;
    StatisticsElementCounter& count_8;

    virtual void Enable() override;
    virtual void Disable() override;

    void CountFieldTypes(const std::vector<uint8_t>& field_values);

    protected:

    std::function<void(StatisticsCollectorFieldTypes&, const std::vector<uint8_t>&)> CountFieldTypesFunction;

    void _CountFieldTypes(const std::vector<uint8_t>& field_values);

    virtual StatisticsCollector* CreateNew() const override;
};

#endif
