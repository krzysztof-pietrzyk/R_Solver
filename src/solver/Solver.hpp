#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "../algorithms/AlgorithmManager.hpp"
#include "../view/GridViewFactory.hpp"
#include "../generators/GridGeneratorFactory.hpp"
#include "../statistics/StatisticsCollector.hpp"

#include "SolverThreadData.hpp"

class Solver
{
    public:

    Solver(uint16_t w, uint16_t h, uint32_t m, SolverThreadData* thread_data_);

    ~Solver();

    void RunForever();

    void Run();

    private:

    GridSelfGenerated* grid;
	GridGenerator* generator;
	GridView* view;
	AlgorithmManager* algorithm_manager;
    StatisticsCollector* statistics_collector;

    SolverThreadData* thread_data;

    uint64_t tries;
	uint64_t wins;
    uint64_t last_read_tries;
    uint64_t last_read_wins;
    const uint32_t fields_to_uncover;

    void UpdateThreadData();
};

#endif
