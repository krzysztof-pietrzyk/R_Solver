#ifndef SOLVER_HPP
#define SOLVER_HPP

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

    Solver(uint16_t w, uint16_t h, uint32_t m, SolverThreadData* thread_data_);

    ~Solver();

    void RunForever();

    void Run();

    void UpdateThreadData();

    private:

    GridInternalImpl* grid;
    GeneratorIf* generator;
	AlgorithmManager* algorithm_manager;
    SolverThreadData* thread_data;
    StatisticsAggregator* statistics_aggregator;
    StatisticsCollectorSolver* statistics_solver;

    void UpdateSolverStatistics();
};

#endif
