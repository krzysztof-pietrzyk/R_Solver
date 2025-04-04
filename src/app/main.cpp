// implemented header

// project includes
#include "../utils/Logger.hpp"
#include "../solver/Solver.hpp"
#include "../solver/SolverThreadData.hpp"
#include "../statistics/StatisticsAggregator.hpp"
#include "../grid/GridDimensions.hpp"

// std includes
#include <thread>
#include <iostream>


using namespace std;

void Run(Solver* solver)
{
	//solver->LoadGridFromString("256|0|4g880k0y80hi0g0a80i22a@w8j@42y04gM0w09g@|!!`|U07w02@kw0c0-g@w0-@2@4@8@g@w0-#w0-");
	solver->RunForever();
}

void CheckStatus(SolverThreadData* data, vector<Solver*> solvers)
{
	const uint32_t status_read_interval = 1U;
	auto time_since_start = std::chrono::duration<int64_t, std::nano>(0);
	auto start_time = std::chrono::high_resolution_clock::now();
	auto current_time = std::chrono::high_resolution_clock::now();
	while(true)
	{
		this_thread::sleep_for(chrono::seconds(status_read_interval));
		current_time = std::chrono::high_resolution_clock::now();
		time_since_start = current_time - start_time;
		double seconds_since_start = time_since_start.count() / double(1E09);
		ostringstream text_to_print = ostringstream();
		text_to_print << string(40, '=') << '\n';
		text_to_print << "Seconds since start: " << seconds_since_start << "\n";

		for(Solver* s : solvers)
		{
			s->UpdateThreadData();
		}
		text_to_print << data->statistics_data->String();
		cout << text_to_print.str();
	}
}

int main()
{
	LOGGER(LogLevel::INIT) << "main";
	const uint16_t threads_number = 10;
	const uint16_t grid_width = 100;
	const uint16_t grid_height = 100;
	const uint32_t grid_mines = 2440;

	cout << "Attempting to run " << threads_number << " threads on " << grid_width << "x" << grid_height << " grid with " << grid_mines << " mines" << endl;

	SolverThreadData* data = new SolverThreadData();

	vector<thread> solver_threads;
	vector<Solver*> solvers;
	GridDimensions grid_dimensions = GridDimensions(grid_width, grid_height, grid_mines);
	for(size_t i = 0; i < threads_number; ++i)
	{
		Solver* s = new Solver(grid_dimensions, data);
		solvers.push_back(s);
		solver_threads.push_back(thread(Run, s));
	}
	thread status = thread(CheckStatus, data, solvers);
	for(size_t i = 0; i < threads_number; ++i) solver_threads[i].join();
	status.join();
	
	return 0;
}
