#include "AlgorithmManager.hpp"

const AlgorithmType AlgorithmManager::default_starting_algorithm = AlgorithmType::SIMPLE_CORNERS;

AlgorithmManager::AlgorithmManager(GridManager& grid_) : grid(&grid_)
{
    data = new AlgorithmDataStorage(grid_);
    factory = new AlgorithmFactory(grid_, *data);

    algorithms = std::map<AlgorithmType, Algorithm*>();
    algorithm_transitions = std::map<AlgorithmType, std::map<AlgorithmStatus, AlgorithmType>>();

    CreateAlgorithms();
    ConfigureAlgorithmTransitions();
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
    AlgorithmType current_algorithm = starting_algorithm;
    AlgorithmStatus current_status;
    while(true)
    {
        current_status = algorithms.at(current_algorithm)->Run();

        if(current_status == AlgorithmStatus::GAME_LOST) return false;
        if(current_status == AlgorithmStatus::GAME_WON) return true;
        
        // algorithm_transitions map defines which algorithm should be executed next
        current_algorithm = GetNextAlgorithm(current_algorithm, current_status);
    }
}

AlgorithmType AlgorithmManager::GetNextAlgorithm(const AlgorithmType previous_algorithm, const AlgorithmStatus previous_status) const
{
    try
    {
        const AlgorithmType next_algorithm = algorithm_transitions.at(previous_algorithm).at(previous_status);
        return next_algorithm;
    }
    catch(const std::out_of_range& e)
    {
        throw std::out_of_range("ERROR: AlgorithmManager::GetNextAlgorithm() unhandled AlgorithmStatus for this AlgorithmType!");
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

void AlgorithmManager::ConfigureAlgorithmTransitions()
{
    // This method is only called once in the constructor
    // It defines transitions between algorithms
    // This is where changes can be made to the order of algorithm execution
    algorithm_transitions[AlgorithmType::SIMPLE_CORNERS] = {
        {AlgorithmStatus::SUCCESS, AlgorithmType::REFRESH_BORDER},
        {AlgorithmStatus::NO_MOVES, AlgorithmType::COMBINATIONS_LEAST_RISKY}};

    algorithm_transitions[AlgorithmType::REFRESH_BORDER] = {
        {AlgorithmStatus::NO_STATUS, AlgorithmType::LAYER_ONE}};

    algorithm_transitions[AlgorithmType::LAYER_ONE] = {
        {AlgorithmStatus::SUCCESS, AlgorithmType::REFRESH_BORDER},
        {AlgorithmStatus::NO_MOVES, AlgorithmType::REFRESH_SECTIONS}};

    algorithm_transitions[AlgorithmType::REFRESH_SECTIONS] = {
        {AlgorithmStatus::NO_STATUS, AlgorithmType::LAYER_TWO}};

    algorithm_transitions[AlgorithmType::LAYER_TWO] = {
        {AlgorithmStatus::SUCCESS, AlgorithmType::REFRESH_BORDER},
        {AlgorithmStatus::NO_MOVES, AlgorithmType::REFRESH_SEGMENTS}};

    algorithm_transitions[AlgorithmType::REFRESH_SEGMENTS] = {
        {AlgorithmStatus::NO_STATUS, AlgorithmType::REFRESH_SUBSEGMENTS}};

    algorithm_transitions[AlgorithmType::REFRESH_SUBSEGMENTS] = {
        {AlgorithmStatus::NO_STATUS, AlgorithmType::REFRESH_FACE}};

    algorithm_transitions[AlgorithmType::REFRESH_FACE] = {
        {AlgorithmStatus::NO_STATUS, AlgorithmType::REFRESH_COMBINATIONS}};

    algorithm_transitions[AlgorithmType::REFRESH_COMBINATIONS] = {
        {AlgorithmStatus::NO_STATUS, AlgorithmType::COMBINATIONS_SAFE_MOVES}};

    algorithm_transitions[AlgorithmType::COMBINATIONS_SAFE_MOVES] = {
        {AlgorithmStatus::SUCCESS, AlgorithmType::REFRESH_BORDER},
        {AlgorithmStatus::NO_MOVES, AlgorithmType::SIMPLE_CORNERS}};

    algorithm_transitions[AlgorithmType::COMBINATIONS_LEAST_RISKY] = {
        {AlgorithmStatus::SUCCESS, AlgorithmType::REFRESH_BORDER},
        {AlgorithmStatus::NO_MOVES, AlgorithmType::GIVE_UP}};

    algorithm_transitions[AlgorithmType::GIVE_UP] = {};
}
