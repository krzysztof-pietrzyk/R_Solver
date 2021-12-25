#ifndef Solver_hpp
#define Solver_hpp

#include "AlgorithmManager.hpp"
#include "GridViewFactory.hpp"
#include "GridGeneratorFactory.hpp"

class Solver
{
    public:

    Solver(unsigned short int w, unsigned short int h, unsigned int m);

    ~Solver();

    void RunForever();

    private:

    GridSelfGenerated* grid;
	GridGenerator* generator;
	GridView* view;
	AlgorithmManager* algorithm_manager;
};

#endif
