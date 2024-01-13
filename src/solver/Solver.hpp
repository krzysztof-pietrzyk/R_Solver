#ifndef SOLVER_HPP
#define SOLVER_HPP

// project includes
#include "../statistics/StatisticsProducer.hpp"

// std includes
#include <bitset>

// forward declarations
class Grid;
class GeneratorInternal;
class GeneratorExternal;
class ViewIf;
class AlgorithmExecutor;
class SolverThreadData;
class StatisticsAggregator;
class StatisticsElementAverage;
class StatisticsElementCounter;
class StatisticsElementMax;
struct GridDimensions;


class Solver : public StatisticsProducer
{
    public:

    Solver(GridDimensions grid_dimensions, SolverThreadData* thread_data_);

    ~Solver();

    void RunForever();

    void Run();

    void UpdateThreadData();

    void LoadGridFromString(const std::string& grid_string);

    private:

    Grid* grid;
    GeneratorInternal* generator_internal;
    GeneratorExternal* generator_external;
    ViewIf* view;
	AlgorithmExecutor* algorithm_executor;
    SolverThreadData* thread_data;
    StatisticsAggregator* statistics_aggregator;

    StatisticsElementCounter* games_played;
    StatisticsElementCounter* games_won;
    StatisticsElementCounter* games_lost;
    StatisticsElementCounter* total_flagged_mines;
    StatisticsElementCounter* total_uncovered_fields;
    StatisticsElementMax* best_win_streak;
    StatisticsElementMax* best_of_100;
    StatisticsElementAverage* average_win_streak;
    StatisticsElementAverage* average_win_rate;

    uint64_t current_win_streak;
    std::bitset<100> best_of_100_set;
    uint8_t best_of_100_index;

    void CreateStatisticsElements();

    void UpdateSolverStatistics();

    void UpdateWinStreakStatistics(bool is_win);
};

#endif
