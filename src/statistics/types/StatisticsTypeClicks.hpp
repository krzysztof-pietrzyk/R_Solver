#ifndef STATISTICS_TYPE_CLICKS_HPP
#define STATISTICS_TYPE_CLICKS_HPP

#include "StatisticsType.hpp"

class StatisticsTypeClicks : public StatisticsType
{
    public:

    StatisticsTypeClicks();

    ~StatisticsTypeClicks();

    virtual void CopyToOutput(StatisticsType& output_data) override;

    uint64_t left_clicks;
    uint64_t wasted_left_clicks;
    uint64_t right_clicks;
    uint64_t wasted_right_clicks;
};

#endif
