#ifndef AlgorithmTransitionManager_hpp
#define AlgorithmTransitionManager_hpp

#include "AlgorithmType.hpp"
#include "AlgorithmStatus.hpp"

#include <map>

class AlgorithmTransitionManager
{
    public:

    AlgorithmTransitionManager();

    ~AlgorithmTransitionManager();

    void AddTransition(const AlgorithmType previous_type, const AlgorithmStatus previous_status, const AlgorithmType next_type);

    void DeleteTransition(const AlgorithmType type, const AlgorithmStatus status);

    AlgorithmType GetNext(const AlgorithmType previous_type, const AlgorithmStatus previous_status) const;

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
