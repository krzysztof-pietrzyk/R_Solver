#include <iostream>
#include <iomanip>
#include <cstring>

#include "AlgorithmManager.hpp"
#include "GridViewFactory.hpp"
#include "GridGeneratorFactory.hpp"

using namespace std;

int main()
{
	GridSelfGenerated* m = new GridSelfGenerated(9, 9, 10);
	GridGenerator* g = GridGeneratorFactory::Create(GridGeneratorType::GENERATOR_UNSAFE, *m);
	GridView* v = GridViewFactory::Create(GridViewType::GRID_VIEW_CONSOLE, *m);
	AlgorithmManager a = AlgorithmManager(*m);

	unsigned long int tries = 0;
	unsigned long int wins = 0;
	const unsigned int fields_to_uncover = m->S - m->M;
	while(true)
	{
		tries++;
		g->Generate();
		m->Clear();
		a.RunAll();
		if(m->visible_fields_index == fields_to_uncover) wins++;
		if(tries % 10000 == 0)
		{
			v->Display();
			cout << "Left clicks: " << m->left_click_counter << "   Right clicks: " << m->right_click_counter << endl;
			cout << "Tries: " << tries << ", Wins: " << wins << ", Win ratio: " << 100 * float(wins) / tries << "%" << endl;
		}
	}
	
	return 0;
}
