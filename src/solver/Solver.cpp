#include "Solver.hpp"

Solver::Solver(GridDimensions grid_dimensions, SolverThreadData* thread_data_) :
    grid(new GridInternal(grid_dimensions)),
    generator(GeneratorFactory::Create(GeneratorType::SAFE, *grid)),
	view(ViewFactory::Create(ViewType::CONSOLE, *grid)),
    algorithm_executor(new AlgorithmExecutor(*grid)),
	statistics_aggregator(new StatisticsAggregator()),
	thread_data(thread_data_)
{
	LOGGER(LogLevel::INIT) << "Solver";
	CreateStatisticsElements();
	const std::map<AlgorithmType, Algorithm*>& algorithms = algorithm_executor->GetAlgorithmsMap();
	for(const auto& item : algorithms)
	{
		statistics_aggregator->RegisterStatisticsProducer(GetAlgorithmTypeLabel(item.first), (StatisticsProducer*)(item.second));
	}
	statistics_aggregator->RegisterStatisticsProducer(Labels::Producers::GENERATOR, (StatisticsProducer*)(generator));
	statistics_aggregator->RegisterStatisticsProducer(Labels::Producers::SOLVER, (StatisticsProducer*)(this));

	thread_data->mut.lock();
	thread_data->SetAggregatorIfEmpty(statistics_aggregator);
	thread_data->mut.unlock();
}

Solver::~Solver()
{
    delete algorithm_executor;
    delete generator;
	delete view;
    delete grid;
	delete thread_data;
	delete statistics_aggregator;
}

void Solver::RunForever()
{
	LOGGER(LogLevel::DEBUG) << "Solver::RunForever";
	while(true)
	{
		LOGGER(LogLevel::DEBUG3) << "Solver::RunForever loop";
		generator->GenerateGrid();
		algorithm_executor->RunAll();
		UpdateSolverStatistics();
	}
}

void Solver::Run()
{
	generator->GenerateGrid();
	algorithm_executor->RunAll();
	UpdateSolverStatistics();
	view->Display();
}

void Solver::UpdateThreadData()
{
	LOGGER(LogLevel::DEBUG) << "Solver::UpdateThreadData()";
	thread_data->mut.lock();
	statistics_aggregator->FlushToOutput(thread_data->statistics_data);
	thread_data->mut.unlock();
	LOGGER(LogLevel::DEBUG) << "Solver::UpdateThreadData() done";
}

void Solver::CreateStatisticsElements()
{
    games_played = new StatisticsElementCounter();
    games_won = new StatisticsElementCounter();
    games_lost = new StatisticsElementCounter();
    games_abandoned = new StatisticsElementCounter();
    total_flagged_mines = new StatisticsElementCounter();
    total_uncovered_fields = new StatisticsElementCounter();
    statistics_collector->AddElement(Labels::Collectors::Solver::GAMES_PLAYED, games_played);
    statistics_collector->AddElement(Labels::Collectors::Solver::GAMES_WON, games_won);
    statistics_collector->AddElement(Labels::Collectors::Solver::GAMES_LOST, games_lost);
    statistics_collector->AddElement(Labels::Collectors::Solver::GAMES_ABANDONED, games_abandoned);
    statistics_collector->AddElement(Labels::Collectors::Solver::TOTAL_MINES_FLAGGED, total_flagged_mines);
    statistics_collector->AddElement(Labels::Collectors::Solver::TOTAL_FIELDS_UNCOVERED, total_uncovered_fields);
}

void Solver::UpdateSolverStatistics()
{
	*games_played += 1;
	*total_flagged_mines += grid->GetFlaggedFields().Index();
	uint32_t uncovered_fields = grid->GetVisibleFields().Index();
	if(grid->IsLost())
	{
		*games_lost += 1;
		*total_uncovered_fields += uncovered_fields - 1;  // -1 because the exploded mine doesn't count
	}
	else if(grid->IsWon())
	{
		*games_won += 1;
		*total_uncovered_fields += uncovered_fields;
	}
	else  // Abandoned game, neither lost or won
	{
		*games_abandoned += 1;
		*total_uncovered_fields += uncovered_fields;
	}
}
