#include "StatisticsTypeClicks.hpp"

StatisticsTypeClicks::StatisticsTypeClicks() :
    left_clicks(data_elements[Labels::Data::Clicks::LEFT_CLICKS]),
    wasted_left_clicks(data_elements[Labels::Data::Clicks::WASTED_LEFT_CLICKS]),
    right_clicks(data_elements[Labels::Data::Clicks::RIGHT_CLICKS]),
    wasted_right_clicks(data_elements[Labels::Data::Clicks::WASTED_RIGHT_CLICKS])
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
