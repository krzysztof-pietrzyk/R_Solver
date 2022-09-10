#include <thread>
#include <vector>
#include <chrono>
#include <ctime>
#include <iostream>

#include "../solver/Solver.hpp"

using namespace std;


void Run(Solver* solver)
{
	solver->RunForever();
}

void CheckStatus(SolverThreadData* data)
{
	const unsigned int status_read_interval = 5;
	auto time_since_start = std::chrono::duration<int64_t, std::nano>(0);
	unsigned long int games_played = 0;
	unsigned long int games_played_last = 0;
	double completion = 0.0;
	unsigned long int wins = 0;
	unsigned long int wins_last = 0;
	float win_ratio = 0.0;
	float games_per_second_avg = 0.0;
	float wins_per_second_avg = 0.0;
	float completion_rate_avg = 0.0;
	auto start_time = std::chrono::high_resolution_clock::now();
	auto current_time = std::chrono::high_resolution_clock::now();
	cout << "+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+\n";
	cout << "|SECONDS SINCE START |    GAMES PLAYED    |     GAMES WON      |  WON/PLAYED RATIO  |AVG COMPLETION RATE |  AVG GAMES/SECOND  |\n";
	cout << "+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+\n";
	while(true)
	{
		this_thread::sleep_for(chrono::seconds(status_read_interval));
		current_time = std::chrono::high_resolution_clock::now();

		data->mut.lock();
		games_played = data->tries;
		wins = data->wins;
		completion = data->completion;
		data->mut.unlock();

		time_since_start = current_time - start_time;
		float seconds_since_start = time_since_start.count() / float(1E09);
		win_ratio = float(wins) / float(games_played);
		games_per_second_avg = float(games_played) / float(seconds_since_start);
		wins_per_second_avg = float(wins) / float(seconds_since_start);
		completion_rate_avg = completion / float(games_played);
		wins_last = wins;
		games_played_last = games_played;

		cout << "|" << right << setw(20) << seconds_since_start << 
		        "|" << right << setw(20) << games_played << 
				"|" << right << setw(20) << wins << 
				"|" << left << setw(20) << win_ratio << 
				"|" << left << setw(20) << completion_rate_avg << 
				"|" << left << setw(20) << games_per_second_avg << "|\n";
	}
}

int main()
{
	const unsigned short int threads_number = 1;
	const unsigned short int grid_width = 30;
	const unsigned short int grid_height = 16;
	const unsigned int grid_mines = 99;

	cout << "Attempting to run " << threads_number << " threads on " << grid_width << "x" << grid_height << " grid with " << grid_mines << " mines" << endl;

	SolverThreadData* data = new SolverThreadData();

	vector<thread> solver_threads;
	for(size_t i = 0; i < threads_number; i++) 
		solver_threads.push_back(thread(Run, new Solver(grid_width, grid_height, grid_mines, data)));
	thread status = thread(CheckStatus, data);
	for(size_t i = 0; i < threads_number; i++) solver_threads[i].join();
	status.join();
	
	return 0;
}



// #include <thread>
// #include <vector>
// #include <chrono>
// #include <ctime>
// #include <iostream>

// #include "solver/Solver.hpp"

// using namespace std;


// int main()
// {
// 	Solver s = Solver(30, 16, 99, nullptr);
// 	s.Run();
	
// 	return 0;
// }
