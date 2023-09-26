#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "../grid/Grid.hpp"
#include "../grid/GridInternal.hpp"
#include "../algorithms/AlgorithmExecutor.hpp"
#include "../view/ViewFactory.hpp"
#include "../generators/GeneratorFactory.hpp"
#include "../statistics/StatisticsAggregator.hpp"
#include "../statistics/StatisticsProducer.hpp"
#include "../statistics/collectors/StatisticsCollectorSolver.hpp"

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
    StatisticsCollectorSolver* statistics_solver;

    void UpdateSolverStatistics();
};

#endif
