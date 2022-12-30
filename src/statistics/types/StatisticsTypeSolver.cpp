#include "StatisticsTypeSolver.hpp"

StatisticsTypeSolver::StatisticsTypeSolver() :
    games_played(data_elements["Games played"]),
    games_won(data_elements["Games won"]),
    games_abandoned(data_elements["Games abandoned"]),
    uncovered_fields(data_elements["Uncovered fields"])
{
    games_played = 0U;
    games_won = 0U;
    games_abandoned = 0U;
    uncovered_fields = 0U;
}

StatisticsTypeSolver::~StatisticsTypeSolver()
{

}

StatisticsType* StatisticsTypeSolver::CreateNew() const
{
    return new StatisticsTypeSolver();
}
