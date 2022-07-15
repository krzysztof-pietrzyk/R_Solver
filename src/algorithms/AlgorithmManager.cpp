#include "AlgorithmManager.hpp"

AlgorithmManager::AlgorithmManager(GridManager& grid_) : grid(&grid_)
{
    data = new AlgorithmDataStorage(grid_);
    factory = new AlgorithmFactory(grid_, *data);

    algorithms = std::map<AlgorithmType, Algorithm*>();
    algorithms[AlgorithmType::ALGORITHM_LAYER_ONE] = factory->Create(AlgorithmType::ALGORITHM_LAYER_ONE);
    algorithms[AlgorithmType::ALGORITHM_LAYER_TWO] = factory->Create(AlgorithmType::ALGORITHM_LAYER_TWO);
	algorithms[AlgorithmType::ALGORITHM_SIMPLE_CORNERS] = factory->Create(AlgorithmType::ALGORITHM_SIMPLE_CORNERS);
	algorithms[AlgorithmType::ALGORITHM_REFRESH_BORDER] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_BORDER);
    algorithms[AlgorithmType::ALGORITHM_REFRESH_SECTIONS] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_SECTIONS);
    algorithms[AlgorithmType::ALGORITHM_REFRESH_SEGMENTS] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_SEGMENTS);
    algorithms[AlgorithmType::ALGORITHM_REFRESH_SUBSEGMENTS] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_SUBSEGMENTS);
    algorithms[AlgorithmType::ALGORITHM_REFRESH_FACE] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_FACE);
    algorithms[AlgorithmType::ALGORITHM_REFRESH_COMBINATIONS] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_COMBINATIONS);
    algorithms[AlgorithmType::ALGORITHM_SURE_MOVES_FROM_COMBINATIONS] = factory->Create(AlgorithmType::ALGORITHM_SURE_MOVES_FROM_COMBINATIONS);
    algorithms[AlgorithmType::ALGORITHM_SAFEST_MOVE_FROM_COMBINATIONS] = factory->Create(AlgorithmType::ALGORITHM_SAFEST_MOVE_FROM_COMBINATIONS);
}

AlgorithmManager::~AlgorithmManager()
{
    delete factory;
    delete data;
    for(auto iter = algorithms.begin(); iter != algorithms.end(); ++iter)
    {
        delete iter->second;
    }
}

bool AlgorithmManager::RunAll()
{
    data->Clear();
    bool clueless = false;
    algorithms[AlgorithmType::ALGORITHM_SIMPLE_CORNERS]->Run();
    while(true)
    {
        if(clueless)
        {
            if(algorithms[AlgorithmType::ALGORITHM_SIMPLE_CORNERS]->Run() == AlgorithmResult::NO_MOVES)
            {
                if(algorithms[AlgorithmType::ALGORITHM_SAFEST_MOVE_FROM_COMBINATIONS]->Run() == AlgorithmResult::NO_MOVES)
                {
                    return false;
                }
            }
            else clueless = false;
        }
        if(!grid->is_lost && grid->visible_fields_index == grid->S - grid->M) { return true; }
        if(grid->is_lost) return false;
        do
        {
            algorithms[AlgorithmType::ALGORITHM_REFRESH_BORDER]->Run();
        } while (algorithms[AlgorithmType::ALGORITHM_LAYER_ONE]->Run() == AlgorithmResult::SUCCESS);
        algorithms[AlgorithmType::ALGORITHM_REFRESH_SECTIONS]->Run();
        if(algorithms[AlgorithmType::ALGORITHM_LAYER_TWO]->Run() == AlgorithmResult::SUCCESS) continue;
        if(!grid->is_lost && grid->visible_fields_index == grid->S - grid->M) { return true; }
        algorithms[AlgorithmType::ALGORITHM_REFRESH_SEGMENTS]->Run();
        algorithms[AlgorithmType::ALGORITHM_REFRESH_SUBSEGMENTS]->Run();
        algorithms[AlgorithmType::ALGORITHM_REFRESH_FACE]->Run();
        algorithms[AlgorithmType::ALGORITHM_REFRESH_COMBINATIONS]->Run();
        if(!grid->is_lost && grid->visible_fields_index == grid->S - grid->M) { return true; }
        if(algorithms[AlgorithmType::ALGORITHM_SURE_MOVES_FROM_COMBINATIONS]->Run() == AlgorithmResult::SUCCESS) continue; 

        clueless = true;
    }
}
