#include <thread>
#include <vector>
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <ostream>

#include "../utils/Logger.hpp"
#include "../solver/Solver.hpp"
#include "../grid/GridDimensions.hpp"

using namespace std;


void Run(Solver* solver)
{
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

		for(Solver* s : solvers)
		{
			s->UpdateThreadData();
		}
		ostringstream text_to_print = ostringstream();
		text_to_print << "\nSeconds since start: " << seconds_since_start << "\n";
		for(const auto& item : data->statistics_data)
		{
			const string& label = item.first;
			const vector<StatisticsCollector*>& labelled_data_vector = item.second;
			text_to_print << label << "\n";
			for(const StatisticsCollector* labelled_data : labelled_data_vector)
			{
				const auto& labelled_data_statistics = labelled_data->GetStatistics();
				for(const auto& temp : labelled_data_statistics)
				{
					text_to_print << "\t" << temp.first << ": " << temp.second->String() << "\n";
				}
			}
		}
		cout << text_to_print.str();

	}
}

int main()
{
	LOGGER(LogLevel::INIT) << "main";
	const uint16_t threads_number = 1;
	const uint16_t grid_width = 30;
	const uint16_t grid_height = 16;
	const uint32_t grid_mines = 99;

	cout << "Attempting to run " << threads_number << " threads on " << grid_width << "x" << grid_height << " grid with " << grid_mines << " mines" << endl;

	SolverThreadData* data = new SolverThreadData();

	vector<thread> solver_threads;
	vector<Solver*> solvers;
	GridDimensions grid_dimensions = GridDimensions(grid_width, grid_height, grid_mines);
	for(size_t i = 0; i < threads_number; i++)
	{
		Solver* s = new Solver(grid_dimensions, data);
		solvers.push_back(s);
		solver_threads.push_back(thread(Run, s));
	}
	thread status = thread(CheckStatus, data, solvers);
	for(size_t i = 0; i < threads_number; i++) solver_threads[i].join();
	status.join();
	
	return 0;
}
