#include "StatisticsCollectorDecisions.hpp"

StatisticsCollectorDecisions::StatisticsCollectorDecisions() :
    StatisticsCollector(
        StatisticsCollectorStruct({
            {Labels::Collectors::Decisions::LEFT_CLICKS, new StatisticsElementCounter()},
            {Labels::Collectors::Decisions::RIGHT_CLICKS, new StatisticsElementCounter()}})),
    decisions_left_click  ((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::Decisions::LEFT_CLICKS]),
    decisions_right_click ((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::Decisions::RIGHT_CLICKS])
{
    decisions_left_click = 0U;
    decisions_right_click = 0U;
}

StatisticsCollectorDecisions::~StatisticsCollectorDecisions()
{

}

StatisticsCollector* StatisticsCollectorDecisions::CreateNew() const
{
    return new StatisticsCollectorDecisions();
}