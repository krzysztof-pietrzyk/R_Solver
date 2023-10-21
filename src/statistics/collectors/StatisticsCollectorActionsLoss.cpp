#include "StatisticsCollectorActionsLoss.hpp"

StatisticsCollectorActionsLoss::StatisticsCollectorActionsLoss() :
    StatisticsCollector(
        StatisticsCollectorStruct({
            {Labels::Collectors::ActionsLoss::SIMPLE_CORNERS, new StatisticsElementCounter()},
            {Labels::Collectors::ActionsLoss::LEAST_RISKY, new StatisticsElementCounter()},
            {Labels::Collectors::ActionsLoss::OTHER, new StatisticsElementCounter()}})),
    loss_simple_corners           ((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::ActionsLoss::SIMPLE_CORNERS]),
    loss_combinations_least_risky ((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::ActionsLoss::LEAST_RISKY]),
    loss_other                    ((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::ActionsLoss::OTHER])
{
    loss_simple_corners = 0U;
    loss_combinations_least_risky = 0U;
    loss_other = 0U;
}

StatisticsCollectorActionsLoss::~StatisticsCollectorActionsLoss()
{

}

StatisticsCollector* StatisticsCollectorActionsLoss::CreateNew() const
{
    return new StatisticsCollectorActionsLoss();
}
