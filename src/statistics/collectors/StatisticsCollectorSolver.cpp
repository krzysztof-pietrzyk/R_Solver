#include "StatisticsCollectorSolver.hpp"

StatisticsCollectorSolver::StatisticsCollectorSolver() :
    games_played(labelled_data_elements[Labels::Collectors::Solver::GAMES_PLAYED]),
    games_won(labelled_data_elements[Labels::Collectors::Solver::GAMES_WON]),
    games_abandoned(labelled_data_elements[Labels::Collectors::Solver::GAMES_ABANDONED]),
    uncovered_fields(labelled_data_elements[Labels::Collectors::Solver::TOTAL_FIELDS_UNCOVERED])
{
    games_played = 0U;
    games_won = 0U;
    games_abandoned = 0U;
    uncovered_fields = 0U;
}

StatisticsCollectorSolver::~StatisticsCollectorSolver()
{

}

StatisticsCollector* StatisticsCollectorSolver::CreateNew() const
{
    return new StatisticsCollectorSolver();
}
