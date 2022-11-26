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
	double win_ratio = 0.0;
	double games_per_second_avg = 0.0;
	double wins_per_second_avg = 0.0;
	double completion_rate_avg = 0.0;
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
		double seconds_since_start = time_since_start.count() / double(1E09);
		win_ratio = double(wins) / double(games_played);
		games_per_second_avg = double(games_played) / double(seconds_since_start);
		wins_per_second_avg = double(wins) / double(seconds_since_start);
		completion_rate_avg = completion / double(games_played);
		wins_last = wins;
		games_played_last = games_played;

		cout << "|" << right << setw(20) << setprecision(6) << seconds_since_start << 
		        "|" << right << setw(20) << games_played << 
				"|" << right << setw(20) << wins << 
				"|" << left << setw(20) << setprecision(12) << win_ratio << 
				"|" << left << setw(20) << setprecision(12) << completion_rate_avg << 
				"|" << left << setw(20) << setprecision(6) << games_per_second_avg << "|\n";
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


// #include <cstdio>
// #include <iostream>

// int main()
// {
// 	uint32_t a = 1000000000;
// 	char buff[25];
// 	snprintf(buff, sizeof(buff), "ECC");
// 	snprintf(buff, sizeof(buff), "%s_%s", buff, "S");
// 	snprintf(buff, sizeof(buff), "%s_%02x", buff, a);
// 	std::cout << buff << "\n";


// 	return 0;
// }