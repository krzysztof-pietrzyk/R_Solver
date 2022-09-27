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

    private:

    // <key: previous AlgorithmType, value: <key: previous AlgorithmStatus, value: next AlgorithmType>>
    std::map<AlgorithmType, std::map<AlgorithmStatus, AlgorithmType>> transitions;

    void ConfigureDefaultTransitions();
};

#endif
