#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "../algorithms/AlgorithmManager.hpp"
#include "../view/GridViewFactory.hpp"
#include "../generators/GridGeneratorFactory.hpp"
#include "../statistics/StatisticsAggregator.hpp"
#include "../statistics/StatisticsProducer.hpp"
#include "../statistics/collectors/StatisticsCollectorSolver.hpp"

#include "SolverThreadData.hpp"

class Solver : public StatisticsProducer
{
    public:

    Solver(uint16_t w, uint16_t h, uint32_t m, SolverThreadData* thread_data_);

    ~Solver();

    void RunForever();

    void Run();

    void UpdateThreadData();

    private:

    GridSelfGenerated* grid;
	GridGenerator* generator;
	GridView* view;
	AlgorithmManager* algorithm_manager;
    StatisticsAggregator* statistics_aggregator;
    StatisticsCollectorSolver* statistics_solver;

    const uint32_t fields_to_uncover;

    SolverThreadData* thread_data;

    void UpdateSolverStatistics();
};

#endif
