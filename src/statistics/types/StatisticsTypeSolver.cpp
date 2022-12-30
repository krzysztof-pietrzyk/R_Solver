#include "StatisticsTypeSolver.hpp"

StatisticsTypeSolver::StatisticsTypeSolver()
{
    games_played = 0U;
    games_won = 0U;
    games_abandoned = 0U;
    uncovered_fields = 0U;
}

StatisticsTypeSolver::~StatisticsTypeSolver()
{

}

std::map<std::string, uint64_t> StatisticsTypeSolver::GetStatistics() const
{
    std::map<std::string, uint64_t> result = std::map<std::string, uint64_t>();
    result["Games played"] = games_played;
    result["Games won"] = games_won;
    result["Games abandoned"] = games_abandoned;
    result["Total uncovered fields"] = uncovered_fields;
    return result;
}

void StatisticsTypeSolver::operator+= (const StatisticsType& other)
{
    const StatisticsTypeSolver& ref = (const StatisticsTypeSolver&)other;
    games_played += ref.games_played;
    games_won += ref.games_won;
    games_abandoned += ref.games_abandoned;
    uncovered_fields += ref.uncovered_fields;
}

StatisticsType* StatisticsTypeSolver::Clone() const
{
    StatisticsType* clone = new StatisticsTypeSolver();
    ((StatisticsTypeSolver*)clone)->games_played = games_played;
    ((StatisticsTypeSolver*)clone)->games_won = games_won;
    ((StatisticsTypeSolver*)clone)->games_abandoned = games_abandoned;
    ((StatisticsTypeSolver*)clone)->uncovered_fields = uncovered_fields;
    return clone;
}

void StatisticsTypeSolver::Clear()
{
    games_played = 0U;
    games_won = 0U;
    games_abandoned = 0U;
    uncovered_fields = 0U;
}
