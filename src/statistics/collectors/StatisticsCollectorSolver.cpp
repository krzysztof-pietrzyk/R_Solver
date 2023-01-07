#include "StatisticsCollectorSolver.hpp"

StatisticsCollectorSolver::StatisticsCollectorSolver() :
    games_played    ((StatisticsElementUINT64&)(*labelled_data_elements[Labels::Collectors::Solver::GAMES_PLAYED])),
    games_won       ((StatisticsElementUINT64&)(*labelled_data_elements[Labels::Collectors::Solver::GAMES_WON])),
    games_abandoned ((StatisticsElementUINT64&)(*labelled_data_elements[Labels::Collectors::Solver::GAMES_ABANDONED])),
    uncovered_fields((StatisticsElementUINT64&)(*labelled_data_elements[Labels::Collectors::Solver::TOTAL_FIELDS_UNCOVERED]))
{
    labelled_data_elements[Labels::Collectors::Solver::GAMES_PLAYED] = new StatisticsElementUINT64();
    labelled_data_elements[Labels::Collectors::Solver::GAMES_WON] = new StatisticsElementUINT64();
    labelled_data_elements[Labels::Collectors::Solver::GAMES_ABANDONED] = new StatisticsElementUINT64();
    labelled_data_elements[Labels::Collectors::Solver::TOTAL_FIELDS_UNCOVERED] = new StatisticsElementUINT64();

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
