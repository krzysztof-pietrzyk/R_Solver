#include "Solver.hpp"

#include <iostream>
using namespace std;

Solver::Solver(unsigned short int w, unsigned short int h, unsigned int m) :
    grid(new GridSelfGenerated(w, h, m)),
    generator(GridGeneratorFactory::Create(GridGeneratorType::GENERATOR_UNSAFE, *grid)),
    view(GridViewFactory::Create(GridViewType::GRID_VIEW_CONSOLE, *grid)),
    algorithm_manager(new AlgorithmManager(*grid))
{

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
    unsigned long int tries = 0;
	unsigned long int wins = 0;
	const unsigned int fields_to_uncover = grid->S - grid->M;
	while(true)
	{
		tries++;
		generator->Generate();
		grid->Clear();
		algorithm_manager->RunAll();
		if(grid->visible_fields_index == fields_to_uncover)
		{
			wins++;
			view->Display();
			cout << "Left clicks: " << grid->left_click_counter << "   Right clicks: " << grid->right_click_counter << endl;
			cout << "Tries: " << tries << ", Wins: " << wins << ", Win ratio: " << 100 * float(wins) / tries << "%" << endl;
		}
	}
}