#include "Solver.hpp"

Solver::Solver(uint16_t w, uint16_t h, uint32_t m, SolverThreadData* thread_data_) :
    grid(new GridInternalImpl(GridDimensions(w, h, m))),
    generator(GeneratorFactory::Create(GeneratorType::SAFE, *grid)),
    algorithm_manager(new AlgorithmManager(*grid)),
	thread_data(thread_data_)
{
	const std::map<AlgorithmType, Algorithm*>& algorithms = algorithm_manager->GetAlgorithmsMap();
}

Solver::~Solver()
{
    delete algorithm_manager;
    delete generator;
    delete grid;
}

void Solver::RunForever()
{
	while(true)
	{
		generator->GenerateGrid();
		algorithm_manager->RunAll();
	}
}

void Solver::Run()
{
	generator->GenerateGrid();
	algorithm_manager->RunAll();
}
