#include "StatisticsCollectorExecutions.hpp"

StatisticsCollectorExecutions::StatisticsCollectorExecutions() :
    StatisticsCollector(
        StatisticsCollectorStruct({
            {Labels::Collectors::Executions::EXECUTIONS, new StatisticsElementCounter()}})),
    executions((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::Executions::EXECUTIONS])
{
    executions = 0U;
}

StatisticsCollectorExecutions::~StatisticsCollectorExecutions()
{

}

StatisticsCollector* StatisticsCollectorExecutions::CreateNew() const
{
    return new StatisticsCollectorExecutions();
}
