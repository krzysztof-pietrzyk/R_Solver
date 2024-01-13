// implemented header
#include "AlgorithmTransitionManager.hpp"

// project includes
#include "AlgorithmStatus.hpp"
#include "../utils/Logger.hpp"

// std includes


const AlgorithmType AlgorithmTransitionManager::default_starting_algorithm = AlgorithmType::FIRST_MOVE;

AlgorithmTransitionManager::AlgorithmTransitionManager()
{
    LOGGER(LogLevel::INIT) << "AlgorithmTransitionManager";
    transitions = std::map<AlgorithmType, std::map<AlgorithmStatus, AlgorithmType>>();
    ConfigureDefaultTransitions();
    SetStartingAlgorithm(default_starting_algorithm);
}

AlgorithmTransitionManager::~AlgorithmTransitionManager() {}


void AlgorithmTransitionManager::AddTransition(const AlgorithmType type, const AlgorithmStatus status, const AlgorithmType next_type)
{
    transitions[type][status] = next_type;
}

void AlgorithmTransitionManager::DeleteTransition(const AlgorithmType type, const AlgorithmStatus status)
{
    LOGGER_ASSERT_TRY(
        transitions.at(type).erase(status),
        std::out_of_range,
        "AlgorithmTransitionManager::DeleteTransition - unhandled AlgorithmType"
    );
}

AlgorithmType AlgorithmTransitionManager::GetNext(const AlgorithmType type, const AlgorithmStatus status) const
{
    LOGGER_ASSERT_TRY(
        { 
            const AlgorithmType next_algorithm = transitions.at(type).at(status);
            return next_algorithm;
        },
        std::out_of_range,
        "AlgorithmTransitionManager::GetNext - unhandled AlgorithmStatus for this AlgorithmType"
    );
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
    AddTransition(AlgorithmType::FIRST_MOVE, AlgorithmStatus::SUCCESS, AlgorithmType::BORDER);

    AddTransition(AlgorithmType::SIMPLE_CORNERS, AlgorithmStatus::SUCCESS, AlgorithmType::SIMPLE_ACTIONS);
    AddTransition(AlgorithmType::SIMPLE_CORNERS, AlgorithmStatus::NO_MOVES, AlgorithmType::COMBINATIONS_LEAST_RISKY);

    AddTransition(AlgorithmType::BORDER, AlgorithmStatus::NO_STATUS, AlgorithmType::LAYER_ONE);

    AddTransition(AlgorithmType::SIMPLE_ACTIONS, AlgorithmStatus::SUCCESS, AlgorithmType::BORDER);

    AddTransition(AlgorithmType::LAYER_ONE, AlgorithmStatus::SUCCESS, AlgorithmType::SIMPLE_ACTIONS);
    AddTransition(AlgorithmType::LAYER_ONE, AlgorithmStatus::NO_MOVES, AlgorithmType::SECTIONS);

    AddTransition(AlgorithmType::SECTIONS, AlgorithmStatus::NO_STATUS, AlgorithmType::LAYER_TWO);

    AddTransition(AlgorithmType::LAYER_TWO, AlgorithmStatus::SUCCESS, AlgorithmType::SIMPLE_ACTIONS);
    AddTransition(AlgorithmType::LAYER_TWO, AlgorithmStatus::NO_MOVES, AlgorithmType::SEGMENTS);

    AddTransition(AlgorithmType::SEGMENTS, AlgorithmStatus::NO_STATUS, AlgorithmType::SUBSEGMENTS);

    AddTransition(AlgorithmType::SUBSEGMENTS, AlgorithmStatus::NO_STATUS, AlgorithmType::FACE);

    AddTransition(AlgorithmType::FACE, AlgorithmStatus::NO_STATUS, AlgorithmType::COMBINATIONS);

    AddTransition(AlgorithmType::COMBINATIONS, AlgorithmStatus::NO_STATUS, AlgorithmType::COMBINATIONS_SAFE_MOVES);
    AddTransition(AlgorithmType::COMBINATIONS, AlgorithmStatus::FAILURE, AlgorithmType::GIVE_UP);

    AddTransition(AlgorithmType::COMBINATIONS_SAFE_MOVES, AlgorithmStatus::SUCCESS, AlgorithmType::SIMPLE_ACTIONS);
    AddTransition(AlgorithmType::COMBINATIONS_SAFE_MOVES, AlgorithmStatus::NO_MOVES, AlgorithmType::SIMPLE_CORNERS);

    AddTransition(AlgorithmType::COMBINATIONS_LEAST_RISKY, AlgorithmStatus::SUCCESS, AlgorithmType::SIMPLE_ACTIONS);
    AddTransition(AlgorithmType::COMBINATIONS_LEAST_RISKY, AlgorithmStatus::NO_MOVES, AlgorithmType::GIVE_UP);
}
