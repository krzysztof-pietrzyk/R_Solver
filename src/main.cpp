// #include <thread>
// #include <vector>
// #include <chrono>
// #include <ctime>
// #include <iostream>

// #include "Solver.hpp"

// using namespace std;


// void Run(Solver* solver)
// {
// 	solver->RunForever();
// }

// void CheckStatus(SolverThreadData* data)
// {
// 	const unsigned int status_read_interval = 5;
// 	time_t seconds_since_start = 0;
// 	unsigned long int games_played = 0;
// 	unsigned long int games_played_last = 0;
// 	double completion = 0.0;
// 	unsigned long int wins = 0;
// 	unsigned long int wins_last = 0;
// 	float win_ratio = 0.0;
// 	float games_per_second_avg = 0.0;
// 	float wins_per_second_avg = 0.0;
// 	float completion_rate_avg = 0.0;
// 	time_t start_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
// 	time_t current_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
// 	cout << "Seconds_since_start\tGames_played\tWins\tWin_ratio\tCompletion_rate_avg\tGames_per_second_avg\tWins_per_second_avg" << endl;
// 	while(true)
// 	{
// 		this_thread::sleep_for(chrono::seconds(status_read_interval));
// 		current_time = chrono::system_clock::to_time_t(chrono::system_clock::now());

// 		data->mut.lock();
// 		games_played = data->tries;
// 		wins = data->wins;
// 		completion = data->completion;
// 		data->mut.unlock();

// 		seconds_since_start = current_time - start_time;
// 		win_ratio = float(wins) / float(games_played);
// 		games_per_second_avg = float(games_played) / float(seconds_since_start);
// 		wins_per_second_avg = float(wins) / float(seconds_since_start);
// 		completion_rate_avg = completion / float(games_played);
// 		wins_last = wins;
// 		games_played_last = games_played;

// 		cout << seconds_since_start << "\t" << games_played << "\t" << wins << "\t" << win_ratio << "\t" 
// 			<<  completion_rate_avg << "\t" << games_per_second_avg << "\t" << wins_per_second_avg << "\t" << endl;
// 	}
// }

// int main()
// {
// 	const unsigned short int threads_number = 1;
// 	const unsigned short int grid_width = 30;
// 	const unsigned short int grid_height = 16;
// 	const unsigned int grid_mines = 99;

// 	cout << "Attempting to run " << threads_number << " threads on " << grid_width << "x" << grid_height << " grid with " << grid_mines << " mines" << endl;

// 	SolverThreadData* data = new SolverThreadData();

// 	vector<thread> solver_threads;
// 	for(int i = 0; i < threads_number; i++) 
// 		solver_threads.push_back(thread(Run, new Solver(grid_width, grid_height, grid_mines, data)));
// 	thread status = thread(CheckStatus, data);
// 	for(int i = 0; i < threads_number; i++) solver_threads[i].join();
// 	status.join();
	
// 	return 0;
// }


// #include <thread>
// #include <vector>
// #include <chrono>
// #include <ctime>
// #include <iostream>

// #include "Solver.hpp"

// using namespace std;


// int main()
// {
// 	Solver s = Solver(30, 16, 99, nullptr);
// 	s.Run();
	
// 	return 0;
// }

#include <iostream>

#include "Buffer2D.hpp"

using namespace std;

int main()
{
	unsigned int s = 10;
	Buffer2D b = Buffer2D(s, 8);

	for(int i = 0; i < b.Len(); i++)
	{
		Buffer& buffer = b[i];
		buffer += i;
		buffer += buffer[0] * i;
		buffer += buffer[1] * i;
		for(int j = 0; j < buffer.Len(); j++)
		{
			cout << buffer[j] << ", ";
		}
		cout << endl;
	}

	return 0;
}