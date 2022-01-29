#include "Solver.hpp"

Solver::Solver(unsigned short int w, unsigned short int h, unsigned int m, SolverThreadData* thread_data_) :
    grid(new GridSelfGenerated(w, h, m)),
    generator(GridGeneratorFactory::Create(GridGeneratorType::GENERATOR_UNSAFE, *grid)),
    view(GridViewFactory::Create(GridViewType::GRID_VIEW_CONSOLE, *grid)),
    algorithm_manager(new AlgorithmManager(*grid)),
	thread_data(thread_data_)
{
	tries = 0;
	wins = 0;
	last_read_tries = 0;
    last_read_wins = 0;
}

Solver::~Solver()
{
    delete algorithm_manager;
    delete view;
    delete generator;
    delete grid;
}

void Solver::RunForever()
{
	const unsigned int fields_to_uncover = grid->S - grid->M;
	while(true)
	{
		tries++;
		generator->Generate();
		algorithm_manager->RunAll();
		if(!grid->is_lost && grid->visible_fields_index == fields_to_uncover) wins++;
		UpdateThreadData();
	}
}

void Solver::UpdateThreadData()
{
	thread_data->mut.lock();
	thread_data->tries += tries - last_read_tries;
	thread_data->wins += wins - last_read_wins;
	thread_data->mut.unlock();
	last_read_tries = tries;
    last_read_wins = wins;
}
