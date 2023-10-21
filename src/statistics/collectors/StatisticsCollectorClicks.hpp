#ifndef STATISTICS_COLLECTOR_CLICKS_HPP
#define STATISTICS_COLLECTOR_CLICKS_HPP

#include "StatisticsCollector.hpp"
#include "elements/StatisticsElementCounter.hpp"

class StatisticsCollectorClicks : public StatisticsCollector
{
    public:

    StatisticsCollectorClicks();

    ~StatisticsCollectorClicks();

    StatisticsElementCounter& left_clicks;
    StatisticsElementCounter& wasted_left_clicks;
    StatisticsElementCounter& right_clicks;
    StatisticsElementCounter& wasted_right_clicks;

    protected:

    virtual StatisticsCollector* CreateNew() const override;
};

#endif
