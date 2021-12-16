#include <iostream>
#include <iomanip>
#include <cstring>

#include "GridManager.hpp"
#include "AlgorithmFactory.hpp"

using namespace std;

int main()
{
	GridManager m = GridManager(30, 16, 99);
	AlgorithmDataStorage a = AlgorithmDataStorage(m);
	AlgorithmFactory algorithm_factory = AlgorithmFactory(m, a);
	Algorithm* layer_one = algorithm_factory.Create(AlgorithmType::ALGORITHM_LAYER_ONE);
	Algorithm* simple_corners = algorithm_factory.Create(AlgorithmType::ALGORITHM_SIMPLE_CORNERS);
	Algorithm* refresh_border = algorithm_factory.Create(AlgorithmType::ALGORITHM_REFRESH_BORDER);
	unsigned long int tries = 0;
	unsigned long int wins = 0;
	const unsigned int fields_to_uncover = m.S - m.M;
	while(true)
	{
		tries++;
		a.Clear();
		m.Generate();
		while(true)
		{
			if(m.is_lost) break;
			if(!simple_corners->Run()) break;
			do
			{
				refresh_border->Run();
			} while(layer_one->Run());
		}
		if(m.visible_fields_index == fields_to_uncover) wins++;
		if(tries % 10000 == 0)
		{
			cout << "Tries: " << tries << ", Wins: " << wins << ", Ratio: " << float(wins) / tries << endl;
			m.Display();
			cout << "Left clicks: " << m.left_click_counter << "   Right clicks: " << m.right_click_counter << endl;
		}
	}
	
	return 0;
}
