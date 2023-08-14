#include "AlgorithmTransitionManager.hpp"

const AlgorithmType AlgorithmTransitionManager::default_starting_algorithm = AlgorithmType::FIRST_MOVE;

AlgorithmTransitionManager::AlgorithmTransitionManager()
{
    LOGGER(LogLevel::INIT) << "AlgorithmTransitionManager";
    transitions = std::map<AlgorithmType, std::map<AlgorithmStatus, AlgorithmType>>();
    ConfigureDefaultTransitions();
    SetStartingAlgorithm(default_starting_algorithm);
}

AlgorithmTransitionManager::~AlgorithmTransitionManager() {}


void AlgorithmTransitionManager::AddTransition(const AlgorithmType previous_type, const AlgorithmStatus previous_status, const AlgorithmType next_type)
{
    transitions[previous_type][previous_status] = next_type;
}

void AlgorithmTransitionManager::DeleteTransition(const AlgorithmType type, const AlgorithmStatus status)
{
    try
    {
        transitions.at(type).erase(status);
    }
    catch(const std::out_of_range& e)
    {
        throw std::runtime_error("AlgorithmTransitionManager::DeleteTransition - unhandled AlgorithmType");
    }
}

AlgorithmType AlgorithmTransitionManager::GetNext(const AlgorithmType previous_type, const AlgorithmStatus previous_status) const
{
    try
    {
        const AlgorithmType next_algorithm = transitions.at(previous_type).at(previous_status);
        return next_algorithm;
    }
    catch(const std::out_of_range& e)
    {
        throw std::runtime_error("AlgorithmTransitionManager::GetNext - unhandled AlgorithmStatus for this AlgorithmType");
    }
}

void AlgorithmTransitionManager::SetStartingAlgorithm(const AlgorithmType new_starting_algorithm)
{
    this->starting_algorithm = new_starting_algorithm;
}

AlgorithmType AlgorithmTransitionManager::GetStartingAlgorithm() const
{
    return starting_algorithm;
}

void AlgorithmTransitionManager::ConfigureDefaultTransitions()
{
    AddTransition(AlgorithmType::FIRST_MOVE, AlgorithmStatus::SUCCESS, AlgorithmType::REFRESH_BORDER);

    AddTransition(AlgorithmType::SIMPLE_CORNERS, AlgorithmStatus::SUCCESS, AlgorithmType::REFRESH_BORDER);
    AddTransition(AlgorithmType::SIMPLE_CORNERS, AlgorithmStatus::NO_MOVES, AlgorithmType::COMBINATIONS_LEAST_RISKY);

    AddTransition(AlgorithmType::REFRESH_BORDER, AlgorithmStatus::NO_STATUS, AlgorithmType::LAYER_ONE);

    AddTransition(AlgorithmType::LAYER_ONE, AlgorithmStatus::SUCCESS, AlgorithmType::REFRESH_BORDER);
    AddTransition(AlgorithmType::LAYER_ONE, AlgorithmStatus::NO_MOVES, AlgorithmType::REFRESH_SECTIONS);

    AddTransition(AlgorithmType::REFRESH_SECTIONS, AlgorithmStatus::NO_STATUS, AlgorithmType::LAYER_TWO);

    AddTransition(AlgorithmType::LAYER_TWO, AlgorithmStatus::SUCCESS, AlgorithmType::REFRESH_BORDER);
    AddTransition(AlgorithmType::LAYER_TWO, AlgorithmStatus::NO_MOVES, AlgorithmType::REFRESH_SEGMENTS);

    AddTransition(AlgorithmType::REFRESH_SEGMENTS, AlgorithmStatus::NO_STATUS, AlgorithmType::REFRESH_SUBSEGMENTS);

    AddTransition(AlgorithmType::REFRESH_SUBSEGMENTS, AlgorithmStatus::NO_STATUS, AlgorithmType::REFRESH_FACE);

    AddTransition(AlgorithmType::REFRESH_FACE, AlgorithmStatus::NO_STATUS, AlgorithmType::REFRESH_COMBINATIONS);

    AddTransition(AlgorithmType::REFRESH_COMBINATIONS, AlgorithmStatus::NO_STATUS, AlgorithmType::COMBINATIONS_SAFE_MOVES);

    AddTransition(AlgorithmType::COMBINATIONS_SAFE_MOVES, AlgorithmStatus::SUCCESS, AlgorithmType::REFRESH_BORDER);
    AddTransition(AlgorithmType::COMBINATIONS_SAFE_MOVES, AlgorithmStatus::NO_MOVES, AlgorithmType::SIMPLE_CORNERS);

    AddTransition(AlgorithmType::COMBINATIONS_LEAST_RISKY, AlgorithmStatus::SUCCESS, AlgorithmType::REFRESH_BORDER);
    AddTransition(AlgorithmType::COMBINATIONS_LEAST_RISKY, AlgorithmStatus::NO_MOVES, AlgorithmType::GIVE_UP);
}
