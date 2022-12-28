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

void StatisticsTypeClicks::CopyToOutput(StatisticsType& output_data)
{
    StatisticsTypeClicks& ref = (StatisticsTypeClicks&)output_data;
    ref.left_clicks = left_clicks;
    ref.wasted_left_clicks = wasted_left_clicks;
    ref.right_clicks = right_clicks;
    ref.wasted_right_clicks = wasted_right_clicks;
}