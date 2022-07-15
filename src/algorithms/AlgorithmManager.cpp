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
    data->Clear();
    AlgorithmType current_algorithm = AlgorithmType::ALGORITHM_SIMPLE_CORNERS;
    AlgorithmResult current_result = AlgorithmResult::NO_RESULT;
    while(true)
    {
        current_result = algorithms[current_algorithm]->Run();

        if(current_result == AlgorithmResult::GAME_LOST) return false;
        if(current_result == AlgorithmResult::GAME_WON) return true;
        
        current_algorithm = algorithm_transitions[current_algorithm][current_result];
    }
}

void AlgorithmManager::ConfigureAlgorithms()
{
    algorithms = std::map<AlgorithmType, Algorithm*>();
    algorithm_transitions = std::map<AlgorithmType, std::map<AlgorithmResult, AlgorithmType>>();

	algorithms[AlgorithmType::ALGORITHM_SIMPLE_CORNERS] = factory->Create(AlgorithmType::ALGORITHM_SIMPLE_CORNERS);
    algorithm_transitions[AlgorithmType::ALGORITHM_SIMPLE_CORNERS] = {
        {AlgorithmResult::SUCCESS, AlgorithmType::ALGORITHM_REFRESH_BORDER},
        {AlgorithmResult::NO_MOVES, AlgorithmType::ALGORITHM_SAFEST_MOVE_FROM_COMBINATIONS}
    };

	algorithms[AlgorithmType::ALGORITHM_REFRESH_BORDER] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_BORDER);
    algorithm_transitions[AlgorithmType::ALGORITHM_REFRESH_BORDER] = {
        {AlgorithmResult::NO_RESULT, AlgorithmType::ALGORITHM_LAYER_ONE}
    };

    algorithms[AlgorithmType::ALGORITHM_LAYER_ONE] = factory->Create(AlgorithmType::ALGORITHM_LAYER_ONE);
    algorithm_transitions[AlgorithmType::ALGORITHM_LAYER_ONE] = {
        {AlgorithmResult::SUCCESS, AlgorithmType::ALGORITHM_REFRESH_BORDER},
        {AlgorithmResult::NO_MOVES, AlgorithmType::ALGORITHM_REFRESH_SECTIONS}
    };

    algorithms[AlgorithmType::ALGORITHM_REFRESH_SECTIONS] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_SECTIONS);
    algorithm_transitions[AlgorithmType::ALGORITHM_REFRESH_SECTIONS] = {
        {AlgorithmResult::NO_RESULT, AlgorithmType::ALGORITHM_LAYER_TWO}
    };

    algorithms[AlgorithmType::ALGORITHM_LAYER_TWO] = factory->Create(AlgorithmType::ALGORITHM_LAYER_TWO);
    algorithm_transitions[AlgorithmType::ALGORITHM_LAYER_TWO] = {
        {AlgorithmResult::SUCCESS, AlgorithmType::ALGORITHM_REFRESH_BORDER},
        {AlgorithmResult::NO_MOVES, AlgorithmType::ALGORITHM_REFRESH_SEGMENTS}
    };

    algorithms[AlgorithmType::ALGORITHM_REFRESH_SEGMENTS] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_SEGMENTS);
    algorithm_transitions[AlgorithmType::ALGORITHM_REFRESH_SEGMENTS] = {
        {AlgorithmResult::NO_RESULT, AlgorithmType::ALGORITHM_REFRESH_SUBSEGMENTS}
    };

    algorithms[AlgorithmType::ALGORITHM_REFRESH_SUBSEGMENTS] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_SUBSEGMENTS);
    algorithm_transitions[AlgorithmType::ALGORITHM_REFRESH_SUBSEGMENTS] = {
        {AlgorithmResult::NO_RESULT, AlgorithmType::ALGORITHM_REFRESH_FACE}
    };

    algorithms[AlgorithmType::ALGORITHM_REFRESH_FACE] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_FACE);
    algorithm_transitions[AlgorithmType::ALGORITHM_REFRESH_FACE] = {
        {AlgorithmResult::NO_RESULT, AlgorithmType::ALGORITHM_REFRESH_COMBINATIONS}
    };

    algorithms[AlgorithmType::ALGORITHM_REFRESH_COMBINATIONS] = factory->Create(AlgorithmType::ALGORITHM_REFRESH_COMBINATIONS);
    algorithm_transitions[AlgorithmType::ALGORITHM_REFRESH_COMBINATIONS] = {
        {AlgorithmResult::NO_RESULT, AlgorithmType::ALGORITHM_SURE_MOVES_FROM_COMBINATIONS}
    };

    algorithms[AlgorithmType::ALGORITHM_SURE_MOVES_FROM_COMBINATIONS] = factory->Create(AlgorithmType::ALGORITHM_SURE_MOVES_FROM_COMBINATIONS);
    algorithm_transitions[AlgorithmType::ALGORITHM_SURE_MOVES_FROM_COMBINATIONS] = {
        {AlgorithmResult::SUCCESS, AlgorithmType::ALGORITHM_REFRESH_BORDER},
        {AlgorithmResult::NO_MOVES, AlgorithmType::ALGORITHM_SIMPLE_CORNERS}
    };

    algorithms[AlgorithmType::ALGORITHM_SAFEST_MOVE_FROM_COMBINATIONS] = factory->Create(AlgorithmType::ALGORITHM_SAFEST_MOVE_FROM_COMBINATIONS);
    algorithm_transitions[AlgorithmType::ALGORITHM_SAFEST_MOVE_FROM_COMBINATIONS] = {
        {AlgorithmResult::SUCCESS, AlgorithmType::ALGORITHM_REFRESH_BORDER}
    };

}
