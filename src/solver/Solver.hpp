#ifndef SOLVER_HPP
#define SOLVER_HPP

// project includes
#include "../statistics/StatisticsProducer.hpp"

// std includes

// forward declarations
class Grid;
class Generator;
class ViewIf;
class AlgorithmExecutor;
class SolverThreadData;
class StatisticsAggregator;
class StatisticsElementCounter;
struct GridDimensions;


class Solver : public StatisticsProducer
{
    public:

    Solver(GridDimensions grid_dimensions, SolverThreadData* thread_data_);

    ~Solver();

    void RunForever();

    void Run();

    void UpdateThreadData();

    private:

    Grid* grid;
    Generator* generator;
    ViewIf* view;
	AlgorithmExecutor* algorithm_executor;
    SolverThreadData* thread_data;
    StatisticsAggregator* statistics_aggregator;

    StatisticsElementCounter* games_played;
    StatisticsElementCounter* games_won;
    StatisticsElementCounter* games_lost;
    StatisticsElementCounter* games_abandoned;
    StatisticsElementCounter* total_flagged_mines;
    StatisticsElementCounter* total_uncovered_fields;

    void CreateStatisticsElements();

    void UpdateSolverStatistics();
};

#endif
