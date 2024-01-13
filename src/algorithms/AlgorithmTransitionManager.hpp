#ifndef ALGORITHM_TRANSITION_MANAGER_HPP
#define ALGORITHM_TRANSITION_MANAGER_HPP

// project includes
#include "AlgorithmType.hpp"

// std includes
#include <map>

// forward declarations
enum class AlgorithmStatus;


class AlgorithmTransitionManager
{
    public:

    AlgorithmTransitionManager();

    ~AlgorithmTransitionManager();

    void AddTransition(const AlgorithmType type, const AlgorithmStatus status, const AlgorithmType next_type);

    void DeleteTransition(const AlgorithmType type, const AlgorithmStatus status);

    AlgorithmType GetNext(const AlgorithmType type, const AlgorithmStatus status) const;

    void SetStartingAlgorithm(const AlgorithmType new_starting_algorithm);

    AlgorithmType GetStartingAlgorithm() const;

    private:

    // <key: previous AlgorithmType, value: <key: previous AlgorithmStatus, value: next AlgorithmType>>
    std::map<AlgorithmType, std::map<AlgorithmStatus, AlgorithmType>> transitions;
    AlgorithmType starting_algorithm;
    static const AlgorithmType default_starting_algorithm;

    void ConfigureDefaultTransitions();
};

#endif
