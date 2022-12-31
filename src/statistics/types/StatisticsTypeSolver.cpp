#include "StatisticsTypeSolver.hpp"

StatisticsTypeSolver::StatisticsTypeSolver() :
    games_played(data_elements[Labels::Data::Solver::GAMES_PLAYED]),
    games_won(data_elements[Labels::Data::Solver::GAMES_WON]),
    games_abandoned(data_elements[Labels::Data::Solver::GAMES_ABANDONED]),
    uncovered_fields(data_elements[Labels::Data::Solver::TOTAL_FIELDS_UNCOVERED])
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
