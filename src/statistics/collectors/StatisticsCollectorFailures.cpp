#include "StatisticsCollectorFailures.hpp"

StatisticsCollectorFailures::StatisticsCollectorFailures() :
    StatisticsCollector(
        StatisticsCollectorStruct({
            {Labels::Collectors::Executions::FAILURES, new StatisticsElementCounter()}})),
    failures((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::Executions::FAILURES])
{
    failures = 0U;
}

StatisticsCollectorFailures::~StatisticsCollectorFailures()
{

}

StatisticsCollector* StatisticsCollectorFailures::CreateNew() const
{
    return new StatisticsCollectorFailures();
}
