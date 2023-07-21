#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "../grid/GridImpl.hpp"
#include "../grid/GridInternalImpl.hpp"
#include "../algorithms/AlgorithmManager.hpp"
#include "../view/GridViewFactory.hpp"
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

    GridImpl* grid;
    GeneratorIf* generator;
	AlgorithmManager* algorithm_manager;
    SolverThreadData* thread_data;
    StatisticsAggregator* statistics_aggregator;
    StatisticsCollectorSolver* statistics_solver;

    void UpdateSolverStatistics();
};

#endif
