#include <iostream>
#include <iomanip>
#include <cstring>

#include "GridManager.hpp"
#include "AlgorithmFactory.hpp"

using namespace std;

int main()
{
	GridManager m = GridManager(30, 16, 99);
	Algorithm* layer_one = AlgorithmFactory::Create(AlgorithmType::ALGORITHM_LAYER_ONE, m);
	Algorithm* simple_corners = AlgorithmFactory::Create(AlgorithmType::ALGORITHM_SIMPLE_CORNERS, m);
	unsigned long int tries = 0;
	unsigned long int wins = 0;
	const unsigned int fields_to_uncover = m.S - m.M;
	while(true)
	{
		tries++;
		m.Generate();
		while(true)
		{
			if(m.is_lost) break;
			if(!simple_corners->Run()) break;
			m.RefreshBorder();
			while(layer_one->Run());
		}
		if(m.visible_fields_index == fields_to_uncover) wins++;
		if(tries % 100000 == 0)
		{
			cout << "Tries: " << tries << ", Wins: " << wins << ", Ratio: " << float(wins) / tries << endl;
			m.Display();
			cout << "Left clicks: " << m.left_click_counter << "   Right clicks: " << m.right_click_counter << endl;
		}
	}
	
	return 0;
}
