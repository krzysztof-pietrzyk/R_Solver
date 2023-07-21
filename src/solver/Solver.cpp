#include "Solver.hpp"

Solver::Solver(uint16_t w, uint16_t h, uint32_t m, SolverThreadData* thread_data_) :
    grid(new GridInternalImpl(GridDimensions(w, h, m))),
    generator(GeneratorFactory::Create(GeneratorType::SAFE, *grid)),
    algorithm_manager(new AlgorithmManager(*grid)),
	statistics_aggregator(new StatisticsAggregator()),
	thread_data(thread_data_)
{
	LOGGER(LOG_INIT) << "Solver";
	const std::map<AlgorithmType, Algorithm*>& algorithms = algorithm_manager->GetAlgorithmsMap();
	for(const auto& item : algorithms)
	{
		statistics_aggregator->RegisterStatisticsProducer(GetAlgorithmTypeLabel(item.first), (const StatisticsProducer*)(item.second));
	}
	// statistics_aggregator->RegisterStatisticsProducer(Labels::Producers::GRID, (const StatisticsProducer*)(grid));
	statistics_solver = new StatisticsCollectorSolver();
	statistics_collectors.push_back(statistics_solver);
	statistics_aggregator->RegisterStatisticsProducer(Labels::Producers::SOLVER, (const StatisticsProducer*)(this));
}

Solver::~Solver()
{
    delete algorithm_manager;
    delete generator;
    delete grid;
	delete statistics_aggregator;
}

void Solver::RunForever()
{
	while(true)
	{
		generator->GenerateGrid();
		algorithm_manager->RunAll();
		UpdateSolverStatistics();
	}
}

void Solver::Run()
{
	generator->GenerateGrid();
	algorithm_manager->RunAll();
}

void Solver::UpdateThreadData()
{
	thread_data->mut.lock();
	statistics_aggregator->FlushCurrentDataToOutput(thread_data->statistics_data);
	thread_data->mut.unlock();
}

void Solver::UpdateSolverStatistics()
{
	statistics_solver->games_played += 1;
	statistics_solver->flagged_mines += grid->GetFlaggedFields().Index();
	uint32_t uncovered_fields = grid->GetVisibleFields().Index();
	if(grid->IsLost())
	{
		statistics_solver->games_lost += 1;
		statistics_solver->uncovered_fields += uncovered_fields - 1;
	}
	else if(grid->IsWon())
	{
		statistics_solver->games_won += 1;
		statistics_solver->uncovered_fields += uncovered_fields;
	}
	else  // Game was abandoned
	{
		statistics_solver->games_abandoned += 1;
		statistics_solver->uncovered_fields += uncovered_fields;
	}
}
