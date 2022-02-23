#include "Solver.hpp"

Solver::Solver(unsigned short int w, unsigned short int h, unsigned int m, SolverThreadData* thread_data_) :
    grid(new GridSelfGenerated(w, h, m)),
    generator(GridGeneratorFactory::Create(GridGeneratorType::GENERATOR_UNSAFE, *grid)),
    view(GridViewFactory::Create(GridViewType::GRID_VIEW_CONSOLE, *grid)),
    algorithm_manager(new AlgorithmManager(*grid)),
	thread_data(thread_data_), fields_to_uncover(grid->S - grid->M)
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
	while(true)
	{
		tries++;
		generator->Generate();
		grid->CalculateHash();
		algorithm_manager->RunAll();
		if(!grid->is_lost && grid->visible_fields.Len() == fields_to_uncover) wins++;
		UpdateThreadData();
	}
}

void Solver::Run()
{
	const unsigned int fields_to_uncover = grid->S - grid->M;
	generator->Generate();
	algorithm_manager->RunAll();
	view->Display();
}

void Solver::UpdateThreadData()
{
	unsigned int lost = 0;
	if(grid->is_lost) lost = 1;
	float completion_rate = float(grid->visible_fields.Len() - lost) / fields_to_uncover;
	thread_data->mut.lock();
	thread_data->tries += tries - last_read_tries;
	thread_data->wins += wins - last_read_wins;
	thread_data->completion += completion_rate;
	thread_data->mut.unlock();
	last_read_tries = tries;
    last_read_wins = wins;
}
