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

std::string StatisticsTypeClicks::GetStatistics()
{
    return std::to_string(left_clicks);
}