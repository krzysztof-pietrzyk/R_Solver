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
    refresh_subsegments = factory->Create(AlgorithmType::ALGORITHM_REFRESH_SUBSEGMENTS);
    refresh_face = factory->Create(AlgorithmType::ALGORITHM_REFRESH_FACE);
    refresh_combinations = factory->Create(AlgorithmType::ALGORITHM_REFRESH_COMBINATIONS);
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
    delete refresh_subsegments;
    delete refresh_face;
    delete refresh_combinations;
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
        refresh_subsegments->Run();
        refresh_face->Run();
        refresh_combinations->Run();

        clueless = true;
    }
}
