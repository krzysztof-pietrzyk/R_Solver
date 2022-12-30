#ifndef STATISTICS_TYPE_CLICKS_HPP
#define STATISTICS_TYPE_CLICKS_HPP

#include "StatisticsType.hpp"

class StatisticsTypeClicks : public StatisticsType
{
    public:

    StatisticsTypeClicks();

    ~StatisticsTypeClicks();

    virtual std::map<std::string, uint64_t> GetStatistics() const override;

    virtual void operator+= (const StatisticsType& other) override;

    virtual StatisticsType* Clone() const override;

    virtual void Clear() override;

    uint64_t left_clicks;
    uint64_t wasted_left_clicks;
    uint64_t right_clicks;
    uint64_t wasted_right_clicks;
};

#endif
