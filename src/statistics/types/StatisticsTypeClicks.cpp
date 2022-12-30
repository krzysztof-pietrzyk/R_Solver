#include "StatisticsTypeClicks.hpp"

StatisticsTypeClicks::StatisticsTypeClicks() :
    left_clicks(data_elements["Left clicks"]),
    wasted_left_clicks(data_elements["Wasted left clicks"]),
    right_clicks(data_elements["Right clicks"]),
    wasted_right_clicks(data_elements["Wasted right clicks"])
{
    left_clicks = 0U;
    wasted_left_clicks = 0U;
    right_clicks = 0U;
    wasted_right_clicks = 0U;
}

StatisticsTypeClicks::~StatisticsTypeClicks()
{

}

StatisticsType* StatisticsTypeClicks::CreateNew() const
{
    return new StatisticsTypeClicks();
}
