#include "AlgorithmManager.hpp"

AlgorithmManager::AlgorithmManager(GridAccessPlayerIf& grid_) : grid(&grid_)
{
    data = new AlgorithmDataStorage(grid_);

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

const std::map<AlgorithmType, Algorithm*>& AlgorithmManager::GetAlgorithmsMap() const
{
    return algorithms;
}

void AlgorithmManager::CreateAlgorithms()
{
    // This method is only called once in the constructor
    // It creates all Algorithm objects
    algorithms[AlgorithmType::SIMPLE_CORNERS]           = AlgorithmFactory::Create(AlgorithmType::SIMPLE_CORNERS, *grid, *data);
    algorithms[AlgorithmType::REFRESH_BORDER]           = AlgorithmFactory::Create(AlgorithmType::REFRESH_BORDER, *grid, *data);
    algorithms[AlgorithmType::LAYER_ONE]                = AlgorithmFactory::Create(AlgorithmType::LAYER_ONE, *grid, *data);
    algorithms[AlgorithmType::REFRESH_SECTIONS]         = AlgorithmFactory::Create(AlgorithmType::REFRESH_SECTIONS, *grid, *data);
    algorithms[AlgorithmType::LAYER_TWO]                = AlgorithmFactory::Create(AlgorithmType::LAYER_TWO, *grid, *data);
    algorithms[AlgorithmType::REFRESH_SEGMENTS]         = AlgorithmFactory::Create(AlgorithmType::REFRESH_SEGMENTS, *grid, *data);
    algorithms[AlgorithmType::REFRESH_SUBSEGMENTS]      = AlgorithmFactory::Create(AlgorithmType::REFRESH_SUBSEGMENTS, *grid, *data);
    algorithms[AlgorithmType::REFRESH_FACE]             = AlgorithmFactory::Create(AlgorithmType::REFRESH_FACE, *grid, *data);
    algorithms[AlgorithmType::REFRESH_COMBINATIONS]     = AlgorithmFactory::Create(AlgorithmType::REFRESH_COMBINATIONS, *grid, *data);
    algorithms[AlgorithmType::COMBINATIONS_SAFE_MOVES]  = AlgorithmFactory::Create(AlgorithmType::COMBINATIONS_SAFE_MOVES, *grid, *data);
    algorithms[AlgorithmType::COMBINATIONS_LEAST_RISKY] = AlgorithmFactory::Create(AlgorithmType::COMBINATIONS_LEAST_RISKY, *grid, *data);
    algorithms[AlgorithmType::GIVE_UP]                  = AlgorithmFactory::Create(AlgorithmType::GIVE_UP, *grid, *data);
    algorithms[AlgorithmType::FIRST_MOVE]               = AlgorithmFactory::Create(AlgorithmType::FIRST_MOVE, *grid, *data);
}
