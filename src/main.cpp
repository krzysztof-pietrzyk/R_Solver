#include <iostream>
#include <iomanip>
#include <cstring>

#include "Solver.hpp"

using namespace std;

int main()
{
	Solver* solver = new Solver(30, 16, 99);

	solver->RunForever();
	
	return 0;
}
