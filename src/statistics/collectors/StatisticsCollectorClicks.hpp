#ifndef STATISTICS_COLLECTOR_CLICKS_HPP
#define STATISTICS_COLLECTOR_CLICKS_HPP

#include "StatisticsCollector.hpp"
#include "elements/StatisticsElementUINT64.hpp"

class StatisticsCollectorClicks : public StatisticsCollector
{
    public:

    StatisticsCollectorClicks();

    ~StatisticsCollectorClicks();

    StatisticsElementUINT64& left_clicks;
    StatisticsElementUINT64& wasted_left_clicks;
    StatisticsElementUINT64& right_clicks;
    StatisticsElementUINT64& wasted_right_clicks;

    protected:

    virtual StatisticsCollector* CreateNew() const override;
};

#endif
