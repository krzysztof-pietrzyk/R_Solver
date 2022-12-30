#include "StatisticsTypeClicks.hpp"

StatisticsTypeClicks::StatisticsTypeClicks()
{
    left_clicks = 0U;
    wasted_left_clicks = 0U;
    right_clicks = 0U;
    wasted_right_clicks = 0U;
}

StatisticsTypeClicks::~StatisticsTypeClicks()
{

}

std::map<std::string, uint64_t> StatisticsTypeClicks::GetStatistics() const
{
    std::map<std::string, uint64_t> result = std::map<std::string, uint64_t>();
    result["Left clicks"] = left_clicks;
    result["Wasted left clicks"] = wasted_left_clicks;
    result["Right clicks"] = right_clicks;
    result["Wasted right clicks"] = wasted_left_clicks;
    return result;
}

void StatisticsTypeClicks::operator+= (const StatisticsType& other)
{
    const StatisticsTypeClicks& ref = (const StatisticsTypeClicks&)other;
    left_clicks += ref.left_clicks;
    wasted_left_clicks += ref.wasted_left_clicks;
    right_clicks += ref.right_clicks;
    wasted_right_clicks += ref.wasted_right_clicks;
}

StatisticsType* StatisticsTypeClicks::Clone() const
{
    StatisticsType* clone = new StatisticsTypeClicks();
    ((StatisticsTypeClicks*)clone)->left_clicks = left_clicks;
    ((StatisticsTypeClicks*)clone)->wasted_left_clicks = wasted_left_clicks;
    ((StatisticsTypeClicks*)clone)->right_clicks = right_clicks;
    ((StatisticsTypeClicks*)clone)->wasted_right_clicks = wasted_right_clicks;
    return clone;
}

void StatisticsTypeClicks::Clear()
{
    left_clicks = 0U;
    wasted_left_clicks = 0U;
    right_clicks = 0U;
    wasted_right_clicks = 0U;
}
