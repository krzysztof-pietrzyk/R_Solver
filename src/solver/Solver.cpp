#include "Solver.hpp"

Solver::Solver(uint16_t w, uint16_t h, uint32_t m, SolverThreadData* thread_data_) :
    grid(new GridSelfGenerated(w, h, m)),
    generator(GridGeneratorFactory::Create(GridGeneratorType::GENERATOR_SAFE, *grid)),
    view(GridViewFactory::Create(GridViewType::GRID_VIEW_CONSOLE, *grid)),
    algorithm_manager(new AlgorithmManager(*grid)),
	statistics_aggregator(new StatisticsAggregator()),
	thread_data(thread_data_), fields_to_uncover(grid->S - grid->M)
{
	const std::map<AlgorithmType, Algorithm*>& algorithms = algorithm_manager->GetAlgorithmsMap();
	for(const auto& item : algorithms)
	{
		statistics_aggregator->RegisterStatisticsProducer(GetAlgorithmTypeLabel(item.first), (const StatisticsProducer*)(item.second));
	}
	statistics_aggregator->RegisterStatisticsProducer(Labels::Producers::GRID, (const StatisticsProducer*)(grid));
	statistics_solver = new StatisticsCollectorSolver();
	statistics_collectors.push_back(statistics_solver);
	statistics_aggregator->RegisterStatisticsProducer(Labels::Producers::SOLVER, (const StatisticsProducer*)(this));
}

Solver::~Solver()
{
    delete algorithm_manager;
    delete view;
    delete generator;
    delete grid;
	delete statistics_aggregator;
}

void Solver::RunForever()
{
	while(true)
	{
		generator->Generate();
		grid->CalculateHash();
		algorithm_manager->RunAll();
		UpdateSolverStatistics();
	}
}

void Solver::Run()
{
	const uint32_t fields_to_uncover = grid->S - grid->M;
	generator->Generate();
	grid->CalculateHash();
	algorithm_manager->RunAll();
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
	statistics_solver->flagged_mines += grid->flags_index;
	uint32_t uncovered_fields = grid->visible_fields_index;
	if(!grid->is_lost)
	{
		if(uncovered_fields == fields_to_uncover)
		{
			statistics_solver->games_won += 1;
		}
		else
		{
			statistics_solver->games_abandoned += 1;
		}
		statistics_solver->uncovered_fields += uncovered_fields;
	}
	else
	{
		statistics_solver->uncovered_fields += uncovered_fields - 1;
	}
}
