#include "Solver.hpp"

Solver::Solver(GridDimensions grid_dimensions, SolverThreadData* thread_data_) :
    grid(new GridInternal(grid_dimensions)),
    generator(GeneratorFactory::Create(GeneratorType::SAFE, *grid)),
	view(ViewFactory::Create(ViewType::VIEW_CONSOLE, *grid)),
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
	statistics_aggregator->RegisterStatisticsProducer(Labels::Producers::GENERATOR, (const StatisticsProducer*)(generator));
	statistics_solver = new StatisticsCollectorSolver();  // deleted in StatisticsProducer
	statistics_collectors.push_back(statistics_solver);
	statistics_aggregator->RegisterStatisticsProducer(Labels::Producers::SOLVER, (const StatisticsProducer*)(this));
}

Solver::~Solver()
{
    delete algorithm_manager;
    delete generator;
	delete view;
    delete grid;
	delete thread_data;
	delete statistics_aggregator;
}

void Solver::RunForever()
{
	LOGGER(LOG_DEBUG) << "Solver::RunForever";
	while(true)
	{
		LOGGER(LOG_DEBUG3) << "Solver::RunForever loop";
		generator->GenerateGrid();
		algorithm_manager->RunAll();
		UpdateSolverStatistics();
	}
}

void Solver::Run()
{
	generator->GenerateGrid();
	algorithm_manager->RunAll();
	UpdateSolverStatistics();
	view->Display();
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
		statistics_solver->uncovered_fields += uncovered_fields - 1;  // -1 because the exploded mine doesn't count
	}
	else if(grid->IsWon())
	{
		statistics_solver->games_won += 1;
		statistics_solver->uncovered_fields += uncovered_fields;
	}
	else  // Abandoned game, neither lost or won
	{
		statistics_solver->games_abandoned += 1;
		statistics_solver->uncovered_fields += uncovered_fields;
	}
}
