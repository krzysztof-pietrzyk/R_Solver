#ifndef SOLVER_THREAD_DATA_HPP
#define SOLVER_THREAD_DATA_HPP

#include <mutex>

class SolverThreadData
{
    public:

    SolverThreadData();

    ~SolverThreadData();

	std::mutex mut;
	uint64_t tries;
	uint64_t wins;
    double completion;
};

#endif
