#include "AlgorithmTransitionManager.hpp"

const AlgorithmType AlgorithmTransitionManager::default_starting_algorithm = AlgorithmType::FIRST_MOVE;

AlgorithmTransitionManager::AlgorithmTransitionManager()
{
    LOGGER(LOG_INIT) << "AlgorithmTransitionManager";
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
        throw std::out_of_range("ERROR: AlgorithmTransitionManager::DeleteTransition() unhandled AlgorithmType!");
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
        throw std::out_of_range("ERROR: AlgorithmTransitionManager::GetNext() unhandled AlgorithmStatus for this AlgorithmType!");
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
    AddTransition(FIRST_MOVE, SUCCESS, REFRESH_BORDER);

    AddTransition(SIMPLE_CORNERS, SUCCESS, REFRESH_BORDER);
    AddTransition(SIMPLE_CORNERS, NO_MOVES, COMBINATIONS_LEAST_RISKY);

    AddTransition(REFRESH_BORDER, NO_STATUS, LAYER_ONE);

    AddTransition(LAYER_ONE, SUCCESS, REFRESH_BORDER);
    AddTransition(LAYER_ONE, NO_MOVES, REFRESH_SECTIONS);

    AddTransition(REFRESH_SECTIONS, NO_STATUS, LAYER_TWO);

    AddTransition(LAYER_TWO, SUCCESS, REFRESH_BORDER);
    AddTransition(LAYER_TWO, NO_MOVES, REFRESH_SEGMENTS);

    AddTransition(REFRESH_SEGMENTS, NO_STATUS, REFRESH_SUBSEGMENTS);

    AddTransition(REFRESH_SUBSEGMENTS, NO_STATUS, REFRESH_FACE);

    AddTransition(REFRESH_FACE, NO_STATUS, REFRESH_COMBINATIONS);

    AddTransition(REFRESH_COMBINATIONS, NO_STATUS, COMBINATIONS_SAFE_MOVES);

    AddTransition(COMBINATIONS_SAFE_MOVES, SUCCESS, REFRESH_BORDER);
    AddTransition(COMBINATIONS_SAFE_MOVES, NO_MOVES, SIMPLE_CORNERS);

    AddTransition(COMBINATIONS_LEAST_RISKY, SUCCESS, REFRESH_BORDER);
    AddTransition(COMBINATIONS_LEAST_RISKY, NO_MOVES, GIVE_UP);
}
