#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "../grid/Grid.hpp"
#include "../grid/GridInternal.hpp"
#include "../algorithms/AlgorithmExecutor.hpp"
#include "../view/ViewFactory.hpp"
#include "../generators/GeneratorFactory.hpp"
#include "../statistics/StatisticsAggregator.hpp"
#include "../statistics/StatisticsProducer.hpp"
#include "../statistics/elements/StatisticsElementCounter.hpp"

#include "SolverThreadData.hpp"

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
