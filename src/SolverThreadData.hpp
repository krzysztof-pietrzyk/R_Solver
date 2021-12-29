#ifndef SolverThreadData_hpp
#define SolverThreadData_hpp

#include <mutex>

class SolverThreadData
{
    public:

    SolverThreadData();

    ~SolverThreadData();

	std::mutex mut;
	unsigned long int tries;
	unsigned long int wins;
};

#endif
