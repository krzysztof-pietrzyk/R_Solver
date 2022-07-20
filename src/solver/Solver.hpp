#ifndef Solver_hpp
#define Solver_hpp

#include "algorithms/AlgorithmManager.hpp"
#include "view/GridViewFactory.hpp"
#include "generators/GridGeneratorFactory.hpp"

#include "SolverThreadData.hpp"

class Solver
{
    public:

    Solver(unsigned short int w, unsigned short int h, unsigned int m, SolverThreadData* thread_data_);

    ~Solver();

    void RunForever();

    void Run();

    private:

    GridSelfGenerated* grid;
	GridGenerator* generator;
	GridView* view;
	AlgorithmManager* algorithm_manager;

    SolverThreadData* thread_data;

    unsigned long long tries;
	unsigned long long wins;
    unsigned long long last_read_tries;
    unsigned long long last_read_wins;
    const unsigned int fields_to_uncover;

    void UpdateThreadData();
};

#endif
