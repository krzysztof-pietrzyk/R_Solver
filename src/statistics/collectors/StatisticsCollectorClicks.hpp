#ifndef STATISTICS_COLLECTOR_CLICKS_HPP
#define STATISTICS_COLLECTOR_CLICKS_HPP

#include "StatisticsCollector.hpp"

class StatisticsCollectorClicks : public StatisticsCollector
{
    public:

    StatisticsCollectorClicks();

    ~StatisticsCollectorClicks();

    uint64_t& left_clicks;
    uint64_t& wasted_left_clicks;
    uint64_t& right_clicks;
    uint64_t& wasted_right_clicks;

    protected:

    virtual StatisticsCollector* CreateNew() const override;
};

#endif
