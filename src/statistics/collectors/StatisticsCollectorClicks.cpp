#include "StatisticsCollectorClicks.hpp"

StatisticsCollectorClicks::StatisticsCollectorClicks() :
    StatisticsCollector(
        StatisticsCollectorStruct({
            {Labels::Collectors::Clicks::LEFT_CLICKS, new StatisticsElementUINT64()},
            {Labels::Collectors::Clicks::WASTED_LEFT_CLICKS, new StatisticsElementUINT64()},
            {Labels::Collectors::Clicks::RIGHT_CLICKS, new StatisticsElementUINT64()},
            {Labels::Collectors::Clicks::WASTED_RIGHT_CLICKS, new StatisticsElementUINT64()},
            {Labels::Collectors::Clicks::TIMES_LOST, new StatisticsElementUINT64()}})),
    left_clicks        ((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Clicks::LEFT_CLICKS]),
    wasted_left_clicks ((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Clicks::WASTED_LEFT_CLICKS]),
    right_clicks       ((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Clicks::RIGHT_CLICKS]),
    wasted_right_clicks((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Clicks::WASTED_RIGHT_CLICKS]),
    times_caused_loss  ((StatisticsElementUINT64&)*labelled_data_elements[Labels::Collectors::Clicks::TIMES_LOST])
{
    left_clicks = 0U;
    wasted_left_clicks = 0U;
    right_clicks = 0U;
    wasted_right_clicks = 0U;
    times_caused_loss = 0U;
}

StatisticsCollectorClicks::~StatisticsCollectorClicks()
{

}

StatisticsCollector* StatisticsCollectorClicks::CreateNew() const
{
    return new StatisticsCollectorClicks();
}
