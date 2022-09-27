#ifndef AlgorithmManager_hpp
#define AlgorithmManager_hpp

#include <map>

#include "../grid/GridManager.hpp"

#include "AlgorithmFactory.hpp"

class AlgorithmManager
{
    /*
    This class holds references to the algorithms and manages interactions between them.
    In other words, it defines in which order the algorithms should be executed.
    */
    public:

    AlgorithmManager(GridManager& grid_);

    ~AlgorithmManager();

    void SetStartingAlgorithm(const AlgorithmType new_starting_algorithm);

    AlgorithmType GetStartingAlgorithm() const;

    bool RunAll() const;

    private:

    GridManager* grid;
    AlgorithmFactory* factory;
    AlgorithmDataStorage* data;
    AlgorithmType starting_algorithm;
    static const AlgorithmType default_starting_algorithm;

    std::map<AlgorithmType, Algorithm*> algorithms;  // pointers to all algorithms
    // <key: current AlgorithmType, value: <key: current AlgorithmResult, value: next AlgorithmType>>
    std::map<AlgorithmType, std::map<AlgorithmStatus, AlgorithmType>> algorithm_transitions;

    void CreateAlgorithms();

    void ConfigureAlgorithmTransitions();

    AlgorithmType GetNextAlgorithm(const AlgorithmType previous_algorithm, const AlgorithmStatus previous_status) const;
};

#endif
