// implemented header
#include "Solver.hpp"

// project includes
#include "SolverThreadData.hpp"
#include "../algorithms/Algorithm.hpp"
#include "../algorithms/AlgorithmExecutor.hpp"
#include "../generators/GeneratorFactory.hpp"
#include "../generators/GeneratorExternal.hpp"
#include "../generators/GeneratorInternal.hpp"
#include "../grid/GridInternal.hpp"
#include "../grid/state/GridState.hpp"
#include "../statistics/StatisticsAggregator.hpp"
#include "../statistics/StatisticsCollector.hpp"
#include "../statistics/StatisticsLabels.hpp"
#include "../statistics/elements/StatisticsElementAverage.hpp"
#include "../statistics/elements/StatisticsElementCounter.hpp"
#include "../statistics/elements/StatisticsElementMax.hpp"
#include "../utils/Logger.hpp"
#include "../view/ViewFactory.hpp"

// std includes


Solver::Solver(GridDimensions grid_dimensions, SolverThreadData* thread_data_) :
    grid(new GridInternal(grid_dimensions)),
    generator_internal((GeneratorInternal*)GeneratorFactory::Create(GeneratorType::SAFE, *grid)),
	generator_external((GeneratorExternal*)GeneratorFactory::Create(GeneratorType::LOAD_STATE, *grid)),
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
		statistics_aggregator->RegisterStatisticsCollector(GetAlgorithmTypeLabel(item.first), item.second->GetStatisticsCollector());
	}
	statistics_aggregator->RegisterStatisticsCollector(Labels::Collectors::GENERATOR, generator_internal->GetStatisticsCollector());
	statistics_aggregator->RegisterStatisticsCollector(Labels::Collectors::SOLVER, this->GetStatisticsCollector());
	thread_data->mut.lock();
	thread_data->SetAggregatorIfEmpty(statistics_aggregator);
	thread_data->mut.unlock();

    current_win_streak = 0U;
    best_of_100_set = std::bitset<100>(0);
    best_of_100_index = 0U;

	LOGGER(LogLevel::INIT) << "Solver Constructor Complete";
}

Solver::~Solver()
{
    delete algorithm_executor;
    delete generator_internal;
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
		generator_internal->GenerateGrid();
		algorithm_executor->RunAll();
		UpdateSolverStatistics();
	}
}

void Solver::Run()
{
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

void Solver::LoadGridFromString(const std::string& grid_string)
{
	generator_external->SetLoadingSource(new GridState(grid_string));
	generator_external->GenerateGrid();
}

void Solver::CreateStatisticsElements()
{
    games_played = new StatisticsElementCounter();
    games_won = new StatisticsElementCounter();
    games_lost = new StatisticsElementCounter();
    total_flagged_mines = new StatisticsElementCounter();
    total_uncovered_fields = new StatisticsElementCounter();
	best_win_streak = new StatisticsElementMax();
	best_of_100 = new StatisticsElementMax();
	average_win_streak = new StatisticsElementAverage();
	average_win_rate = new StatisticsElementAverage();
    statistics_collector->AddElement(Labels::Elements::Solver::GAMES_PLAYED, games_played);
    statistics_collector->AddElement(Labels::Elements::Solver::GAMES_WON, games_won);
    statistics_collector->AddElement(Labels::Elements::Solver::GAMES_LOST, games_lost);
    statistics_collector->AddElement(Labels::Elements::Solver::TOTAL_MINES_FLAGGED, total_flagged_mines);
    statistics_collector->AddElement(Labels::Elements::Solver::TOTAL_FIELDS_UNCOVERED, total_uncovered_fields);
	statistics_collector->AddElement(Labels::Elements::Solver::BEST_WIN_STREAK, best_win_streak);
    statistics_collector->AddElement(Labels::Elements::Solver::BEST_OF_100, best_of_100);
	statistics_collector->AddElement(Labels::Elements::Solver::AVERAGE_WIN_STREAK, average_win_streak);
    statistics_collector->AddElement(Labels::Elements::Solver::AVERAGE_WIN_RATE, average_win_rate);
}

void Solver::UpdateSolverStatistics()
{
	*games_played += 1;
	*total_flagged_mines += grid->GetFlaggedFields().Index();
	*total_uncovered_fields += grid->GetVisibleFields().Index();  // this includes exploded mines
	if(grid->IsWon())
	{
		*games_won += 1;
		UpdateWinStreakStatistics(true);
	}
	else
	{
		*games_lost += 1;
		UpdateWinStreakStatistics(false);
	}
}

void Solver::UpdateWinStreakStatistics(bool is_win)
{
	best_of_100_set[best_of_100_index++] = is_win;
	if(best_of_100_index >= 100U)
	{
		best_of_100_index = 0U;
	}
	uint32_t current_best_of_100 = best_of_100_set.count();
	best_of_100->CompareAndSet(current_best_of_100);
	average_win_rate->AddEntryToAverage(int(is_win));
	if(is_win)
	{
		++current_win_streak;
	}
	else
	{
		best_win_streak->CompareAndSet(current_win_streak);
		average_win_streak->AddEntryToAverage(current_win_streak);
		current_win_streak = 0U;
	}
}
