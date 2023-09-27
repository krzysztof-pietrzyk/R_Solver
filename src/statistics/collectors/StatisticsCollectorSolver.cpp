#include "StatisticsCollectorSolver.hpp"

StatisticsCollectorSolver::StatisticsCollectorSolver() :
    StatisticsCollector(
        StatisticsCollectorStruct({
            {Labels::Collectors::Solver::GAMES_PLAYED, new StatisticsElementCounter()},
            {Labels::Collectors::Solver::GAMES_WON, new StatisticsElementCounter()},
            {Labels::Collectors::Solver::GAMES_LOST, new StatisticsElementCounter()},
            {Labels::Collectors::Solver::GAMES_ABANDONED, new StatisticsElementCounter()},
            {Labels::Collectors::Solver::TOTAL_FIELDS_UNCOVERED, new StatisticsElementCounter()},
            {Labels::Collectors::Solver::TOTAL_MINES_FLAGGED, new StatisticsElementCounter()}})),
    games_played    ((StatisticsElementCounter&)(*labelled_data_elements[Labels::Collectors::Solver::GAMES_PLAYED])),
    games_won       ((StatisticsElementCounter&)(*labelled_data_elements[Labels::Collectors::Solver::GAMES_WON])),
    games_lost      ((StatisticsElementCounter&)(*labelled_data_elements[Labels::Collectors::Solver::GAMES_LOST])),
    games_abandoned ((StatisticsElementCounter&)(*labelled_data_elements[Labels::Collectors::Solver::GAMES_ABANDONED])),
    uncovered_fields((StatisticsElementCounter&)(*labelled_data_elements[Labels::Collectors::Solver::TOTAL_FIELDS_UNCOVERED])),
    flagged_mines   ((StatisticsElementCounter&)(*labelled_data_elements[Labels::Collectors::Solver::TOTAL_MINES_FLAGGED]))
{
    games_played = 0U;
    games_won = 0U;
    games_lost = 0U;
    games_abandoned = 0U;
    uncovered_fields = 0U;
    flagged_mines = 0U;
}

StatisticsCollectorSolver::~StatisticsCollectorSolver()
{

}

StatisticsCollector* StatisticsCollectorSolver::CreateNew() const
{
    return new StatisticsCollectorSolver();
}
