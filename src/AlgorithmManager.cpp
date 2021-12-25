#include "AlgorithmManager.hpp"

AlgorithmManager::AlgorithmManager(GridManager& grid_)
{
    data = new AlgorithmDataStorage(grid_);
    factory = new AlgorithmFactory(grid_, *data);
    layer_one = factory->Create(AlgorithmType::ALGORITHM_LAYER_ONE);
	simple_corners = factory->Create(AlgorithmType::ALGORITHM_SIMPLE_CORNERS);
	refresh_border = factory->Create(AlgorithmType::ALGORITHM_REFRESH_BORDER);
}

AlgorithmManager::~AlgorithmManager()
{
    delete data;
}

bool AlgorithmManager::RunAll()
{
    data->Clear();
    while(true)
    {
        if(!simple_corners->Run()) return false;
        do
        {
            refresh_border->Run();
        } while (layer_one->Run());
    }
}
