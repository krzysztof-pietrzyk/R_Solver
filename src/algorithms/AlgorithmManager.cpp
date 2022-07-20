#include "AlgorithmManager.hpp"

AlgorithmManager::AlgorithmManager(GridManager& grid_) : grid(&grid_)
{
    data = new AlgorithmDataStorage(grid_);
    factory = new AlgorithmFactory(grid_, *data);

    algorithms = std::map<AlgorithmType, Algorithm*>();
    algorithm_transitions = std::map<AlgorithmType, std::map<AlgorithmStatus, AlgorithmType>>();

    algorithm_metrics_collector = new AlgorithmMetricsCollector(algorithms);

    ConfigureAlgorithms();
}

AlgorithmManager::~AlgorithmManager()
{
    for(auto iter = algorithms.begin(); iter != algorithms.end(); ++iter)
    {
        delete iter->second;
    }
    delete factory;
    delete algorithm_metrics_collector;
    delete data;

}

bool AlgorithmManager::RunAll()
{
    // Run algorithms in defined order until the game is either won or lost
    // returns true if game is won, false if game is lost
    data->Clear();
    // first algorithm (starting strategy)
    AlgorithmType current_algorithm = AlgorithmType::ALGORITHM_SIMPLE_CORNERS;
    AlgorithmStatus current_status = AlgorithmStatus::NO_STATUS;
    while(true)
    {
        current_status = algorithms[current_algorithm]->Run();

        if(current_status == AlgorithmStatus::GAME_LOST)
        {
            algorithm_metrics_collector->UpdateMetrics();
            return false;
        }
        if(current_status == AlgorithmStatus::GAME_WON)
        {
            algorithm_metrics_collector->UpdateMetrics();
            return true;
        }
        // algorithm_transitions map defines which algorithm should be executed next
        current_algorithm = GetNextAlgorithm(current_algorithm, current_status);
    }
}

AlgorithmType AlgorithmManager::GetNextAlgorithm(const AlgorithmType previous_algorithm, const AlgorithmStatus previous_status)
{
    if(algorithm_transitions[previous_algorithm].count(previous_status) == 0)
    {
        // If this is thrown, something is incorrectly configured in AlgorithmManager::ConfigureAlgorithms
        throw std::invalid_argument("ERROR: AlgorithmManager::GetNextAlgorithm() unhandled AlgorithmStatus for this AlgorithmType!");
    }
    return algorithm_transitions[previous_algorithm][previous_status];
}

void AlgorithmManager::ConfigureAlgorithms()
{
    // This method is only called once in the constructor
    // It creates all Algorithm objects and defines the transitions between them
    // This is where changes can be made to the order of algorithm execution

	algorithms[AlgorithmType::ALGORITHM_SIMPLE_CORNERS] = factory->Create(AlgorithmType::ALGORITHM_SIMPLE_CORNERS);
    algorithm_transitions[AlgorithmType::ALGORITHM_SIMPLE_CORNERS] = {
        {AlgorithmStatus::SUCCESS, AlgorithmType::ALGORITHM_REFRESH_BORDER},
        {AlgorithmStatus::NO_MOVES, AlgorithmType::ALGORITHM_COMBINATIONS_LEAST_RISKY}
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
        {AlgorithmStatus::NO_STATUS, AlgorithmType::ALGORITHM_COMBINATIONS_SAFE_MOVES}
    };

    algorithms[AlgorithmType::ALGORITHM_COMBINATIONS_SAFE_MOVES] = factory->Create(AlgorithmType::ALGORITHM_COMBINATIONS_SAFE_MOVES);
    algorithm_transitions[AlgorithmType::ALGORITHM_COMBINATIONS_SAFE_MOVES] = {
        {AlgorithmStatus::SUCCESS, AlgorithmType::ALGORITHM_REFRESH_BORDER},
        {AlgorithmStatus::NO_MOVES, AlgorithmType::ALGORITHM_SIMPLE_CORNERS}
    };

    algorithms[AlgorithmType::ALGORITHM_COMBINATIONS_LEAST_RISKY] = factory->Create(AlgorithmType::ALGORITHM_COMBINATIONS_LEAST_RISKY);
    algorithm_transitions[AlgorithmType::ALGORITHM_COMBINATIONS_LEAST_RISKY] = {
        {AlgorithmStatus::SUCCESS, AlgorithmType::ALGORITHM_REFRESH_BORDER}
    };
}
