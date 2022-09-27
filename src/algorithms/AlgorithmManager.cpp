#include "AlgorithmManager.hpp"

const AlgorithmType AlgorithmManager::default_starting_algorithm = AlgorithmType::SIMPLE_CORNERS;

AlgorithmManager::AlgorithmManager(GridManager& grid_) : grid(&grid_)
{
    data = new AlgorithmDataStorage(grid_);
    factory = new AlgorithmFactory(grid_, *data);

    algorithms = std::map<AlgorithmType, Algorithm*>();
    transitions = AlgorithmTransitionManager();

    CreateAlgorithms();
    SetStartingAlgorithm(default_starting_algorithm);
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

void AlgorithmManager::SetStartingAlgorithm(const AlgorithmType new_starting_algorithm)
{
    this->starting_algorithm = new_starting_algorithm;
}

AlgorithmType AlgorithmManager::GetStartingAlgorithm() const
{
    return starting_algorithm;
}

bool AlgorithmManager::RunAll() const
{
    // Run algorithms in defined order until the game is either won or lost
    data->Clear();
    AlgorithmType current_algorithm = GetStartingAlgorithm();
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
}
