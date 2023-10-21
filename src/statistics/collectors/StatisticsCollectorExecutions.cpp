#include "StatisticsCollectorExecutions.hpp"

StatisticsCollectorExecutions::StatisticsCollectorExecutions() :
    StatisticsCollector(
        StatisticsCollectorStruct({
            {Labels::Collectors::Executions::EXECUTIONS, new StatisticsElementCounter()},
            {Labels::Collectors::Executions::SUCCESS, new StatisticsElementCounter()},
            {Labels::Collectors::Executions::NO_MOVES, new StatisticsElementCounter()},
            {Labels::Collectors::Executions::FAILURE, new StatisticsElementCounter()},
            {Labels::Collectors::Executions::GAME_WON, new StatisticsElementCounter()},
            {Labels::Collectors::Executions::GAME_LOST, new StatisticsElementCounter()}})),
    executions((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::Executions::EXECUTIONS]),
    success((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::Executions::SUCCESS]),
    no_moves((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::Executions::NO_MOVES]),
    failure((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::Executions::FAILURE]),
    game_won((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::Executions::GAME_WON]),
    game_lost((StatisticsElementCounter&)*labelled_data_elements[Labels::Collectors::Executions::GAME_LOST])
{
    executions = 0U;
    success = 0U;
    no_moves = 0U;
    failure = 0U;
    game_won = 0U;
    game_lost = 0U;
}

StatisticsCollectorExecutions::~StatisticsCollectorExecutions()
{

}

StatisticsCollector* StatisticsCollectorExecutions::CreateNew() const
{
    return new StatisticsCollectorExecutions();
}
