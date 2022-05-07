#include "AlgorithmManager.hpp"

AlgorithmManager::AlgorithmManager(GridManager& grid_) : grid(&grid_)
{
    data = new AlgorithmDataStorage(grid_);
    factory = new AlgorithmFactory(grid_, *data);
    layer_one = factory->Create(AlgorithmType::ALGORITHM_LAYER_ONE);
    layer_two = factory->Create(AlgorithmType::ALGORITHM_LAYER_TWO);
	simple_corners = factory->Create(AlgorithmType::ALGORITHM_SIMPLE_CORNERS);
	refresh_border = factory->Create(AlgorithmType::ALGORITHM_REFRESH_BORDER);
    refresh_sections = factory->Create(AlgorithmType::ALGORITHM_REFRESH_SECTIONS);
    refresh_segments = factory->Create(AlgorithmType::ALGORITHM_REFRESH_SEGMENTS);
    optimized_segments = factory->Create(AlgorithmType::ALGORITHM_OPTIMIZED_SEGMENTS);
}

AlgorithmManager::~AlgorithmManager()
{
    delete factory;
    delete data;
    delete layer_one;
    delete layer_two;
    delete simple_corners;
    delete refresh_border;
    delete refresh_sections;
    delete refresh_segments;
    delete optimized_segments;
}

bool AlgorithmManager::RunAll()
{
    data->Clear();
    bool clueless = false;
    simple_corners->Run();
    while(true)
    {
        if(clueless)
        {
            if(!simple_corners->Run())
            {
                return false;
            }
            else clueless = false;
        }
        if(grid->is_lost) return false;
        do
        {
            refresh_border->Run();
        } while (layer_one->Run());
        refresh_sections->Run();
        if(layer_two->Run()) continue;
        refresh_segments->Run();
        optimized_segments->Run();

        clueless = true;
    }
}
