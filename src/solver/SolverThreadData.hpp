#ifndef SolverThreadData_hpp
#define SolverThreadData_hpp

#include <mutex>

class SolverThreadData
{
    public:

    SolverThreadData();

    ~SolverThreadData();

	std::mutex mut;
	unsigned long long tries;
	unsigned long long wins;
    double completion;
};

#endif
