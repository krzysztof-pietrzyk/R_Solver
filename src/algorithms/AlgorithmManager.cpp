#include "AlgorithmManager.hpp"

AlgorithmManager::AlgorithmManager(GridManager& grid_) : grid(&grid_)
{
    data = new AlgorithmDataStorage(grid_);
    factory = new AlgorithmFactory(grid_, *data);
    
    ConfigureAlgorithms();
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

bool AlgorithmManager::RunAll()
{
    // Run algorithms in defined order until the game is either won or lost
    data->Clear();
    AlgorithmType current_algorithm = AlgorithmType::ALGORITHM_SIMPLE_CORNERS;
    AlgorithmStatus current_status = AlgorithmStatus::NO_STATUS;
    while(true)
    {
        current_status = algorithms[current_algorithm]->Run();

        if(current_status == AlgorithmStatus::GAME_LOST) return false;
        if(current_status == AlgorithmStatus::GAME_WON) return true;
        
        // algorithm_transitions map defines which algorithm should be executed next
        current_algorithm = algorithm_transitions[current_algorithm][current_status];
    }
}

void AlgorithmManager::ConfigureAlgorithms()
{
    // This method is only called once in the constructor
    // It creates all Algorithm objects and defines the transitions between them
    // This is where changes can be made to the order of algorithm execution
    algorithms = std::map<AlgorithmType, Algorithm*>();
    algorithm_transitions = std::map<AlgorithmType, std::map<AlgorithmStatus, AlgorithmType>>();

	algorithms[AlgorithmType::ALGORITHM_SIMPLE_CORNERS] = factory->Create(AlgorithmType::ALGORITHM_SIMPLE_CORNERS);
    algorithm_transitions[AlgorithmType::ALGORITHM_SIMPLE_CORNERS] = {
        {AlgorithmStatus::SUCCESS, AlgorithmType::ALGORITHM_REFRESH_BORDER},
        {AlgorithmStatus::NO_MOVES, AlgorithmType::ALGORITHM_SAFEST_MOVE_FROM_COMBINATIONS}
    };

	algorithms[AlgorithmType::ALGORITHM_REFRESH_BORDER] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_BORDER);
    algorithm_transitions[AlgorithmType::ALGORITHM_REFRESH_BORDER] = {
        {AlgorithmStatus::NO_STATUS, AlgorithmType::ALGORITHM_LAYER_ONE}
    };

    algorithms[AlgorithmType::ALGORITHM_LAYER_ONE] = factory->Create(AlgorithmType::ALGORITHM_LAYER_ONE);
    algorithm_transitions[AlgorithmType::ALGORITHM_LAYER_ONE] = {
        {AlgorithmStatus::SUCCESS, AlgorithmType::ALGORITHM_REFRESH_BORDER},
        {AlgorithmStatus::NO_MOVES, AlgorithmType::ALGORITHM_REFRESH_SECTIONS}
    };

    algorithms[AlgorithmType::ALGORITHM_REFRESH_SECTIONS] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_SECTIONS);
    algorithm_transitions[AlgorithmType::ALGORITHM_REFRESH_SECTIONS] = {
        {AlgorithmStatus::NO_STATUS, AlgorithmType::ALGORITHM_LAYER_TWO}
    };

    algorithms[AlgorithmType::ALGORITHM_LAYER_TWO] = factory->Create(AlgorithmType::ALGORITHM_LAYER_TWO);
    algorithm_transitions[AlgorithmType::ALGORITHM_LAYER_TWO] = {
        {AlgorithmStatus::SUCCESS, AlgorithmType::ALGORITHM_REFRESH_BORDER},
        {AlgorithmStatus::NO_MOVES, AlgorithmType::ALGORITHM_REFRESH_SEGMENTS}
    };

    algorithms[AlgorithmType::ALGORITHM_REFRESH_SEGMENTS] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_SEGMENTS);
    algorithm_transitions[AlgorithmType::ALGORITHM_REFRESH_SEGMENTS] = {
        {AlgorithmStatus::NO_STATUS, AlgorithmType::ALGORITHM_REFRESH_SUBSEGMENTS}
    };

    algorithms[AlgorithmType::ALGORITHM_REFRESH_SUBSEGMENTS] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_SUBSEGMENTS);
    algorithm_transitions[AlgorithmType::ALGORITHM_REFRESH_SUBSEGMENTS] = {
        {AlgorithmStatus::NO_STATUS, AlgorithmType::ALGORITHM_REFRESH_FACE}
    };

    algorithms[AlgorithmType::ALGORITHM_REFRESH_FACE] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_FACE);
    algorithm_transitions[AlgorithmType::ALGORITHM_REFRESH_FACE] = {
        {AlgorithmStatus::NO_STATUS, AlgorithmType::ALGORITHM_REFRESH_COMBINATIONS}
    };

    algorithms[AlgorithmType::ALGORITHM_REFRESH_COMBINATIONS] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_COMBINATIONS);
    algorithm_transitions[AlgorithmType::ALGORITHM_REFRESH_COMBINATIONS] = {
        {AlgorithmStatus::NO_STATUS, AlgorithmType::ALGORITHM_SURE_MOVES_FROM_COMBINATIONS}
    };

    algorithms[AlgorithmType::ALGORITHM_SURE_MOVES_FROM_COMBINATIONS] = factory->Create(AlgorithmType::ALGORITHM_SURE_MOVES_FROM_COMBINATIONS);
    algorithm_transitions[AlgorithmType::ALGORITHM_SURE_MOVES_FROM_COMBINATIONS] = {
        {AlgorithmStatus::SUCCESS, AlgorithmType::ALGORITHM_REFRESH_BORDER},
        {AlgorithmStatus::NO_MOVES, AlgorithmType::ALGORITHM_SIMPLE_CORNERS}
    };

    algorithms[AlgorithmType::ALGORITHM_SAFEST_MOVE_FROM_COMBINATIONS] = factory->Create(AlgorithmType::ALGORITHM_SAFEST_MOVE_FROM_COMBINATIONS);
    algorithm_transitions[AlgorithmType::ALGORITHM_SAFEST_MOVE_FROM_COMBINATIONS] = {
        {AlgorithmStatus::SUCCESS, AlgorithmType::ALGORITHM_REFRESH_BORDER}
    };
}
