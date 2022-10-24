#include "AlgorithmManager.hpp"

AlgorithmManager::AlgorithmManager(GridManager& grid_) : grid(&grid_)
{
    data = new AlgorithmDataStorage(grid_);
    factory = new AlgorithmFactory(grid_, *data);

    algorithms = std::map<AlgorithmType, Algorithm*>();
    transitions = AlgorithmTransitionManager();

    CreateAlgorithms();
}

AlgorithmManager::~AlgorithmManager()
{
    for(auto iter = algorithms.begin(); iter != algorithms.end(); ++iter)
    {
        delete iter->second;
    }
    delete factory;
    delete data;
}

bool AlgorithmManager::RunAll() const
{
    // Run algorithms in defined order until the game is either won or lost
    data->Clear();
    AlgorithmType current_algorithm = transitions.GetStartingAlgorithm();
    AlgorithmStatus current_status;
    while(true)
    {
        current_status = algorithms.at(current_algorithm)->Run();

        if(current_status == AlgorithmStatus::GAME_LOST) return false;
        if(current_status == AlgorithmStatus::GAME_WON) return true;

        current_algorithm = transitions.GetNext(current_algorithm, current_status);
    }
}

void AlgorithmManager::CreateAlgorithms()
{
    // This method is only called once in the constructor
    // It creates all Algorithm objects
    algorithms[AlgorithmType::SIMPLE_CORNERS]           = factory->Create(AlgorithmType::SIMPLE_CORNERS);
    algorithms[AlgorithmType::REFRESH_BORDER]           = factory->Create(AlgorithmType::REFRESH_BORDER);
    algorithms[AlgorithmType::LAYER_ONE]                = factory->Create(AlgorithmType::LAYER_ONE);
    algorithms[AlgorithmType::REFRESH_SECTIONS]         = factory->Create(AlgorithmType::REFRESH_SECTIONS);
    algorithms[AlgorithmType::LAYER_TWO]                = factory->Create(AlgorithmType::LAYER_TWO);
    algorithms[AlgorithmType::REFRESH_SEGMENTS]         = factory->Create(AlgorithmType::REFRESH_SEGMENTS);
    algorithms[AlgorithmType::REFRESH_SUBSEGMENTS]      = factory->Create(AlgorithmType::REFRESH_SUBSEGMENTS);
    algorithms[AlgorithmType::REFRESH_FACE]             = factory->Create(AlgorithmType::REFRESH_FACE);
    algorithms[AlgorithmType::REFRESH_COMBINATIONS]     = factory->Create(AlgorithmType::REFRESH_COMBINATIONS);
    algorithms[AlgorithmType::COMBINATIONS_SAFE_MOVES]  = factory->Create(AlgorithmType::COMBINATIONS_SAFE_MOVES);
    algorithms[AlgorithmType::COMBINATIONS_LEAST_RISKY] = factory->Create(AlgorithmType::COMBINATIONS_LEAST_RISKY);
    algorithms[AlgorithmType::GIVE_UP]                  = factory->Create(AlgorithmType::GIVE_UP);
    algorithms[AlgorithmType::FIRST_MOVE]               = factory->Create(AlgorithmType::FIRST_MOVE);
}
