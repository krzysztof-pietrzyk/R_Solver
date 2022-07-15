#ifndef AlgorithmSafestMoveFromCombinations_hpp
#define AlgorithmSafestMoveFromCombinations_hpp

#include "Algorithm.hpp"

class AlgorithmSafestMoveFromCombinations : public Algorithm
{
    public:

    AlgorithmSafestMoveFromCombinations(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmSafestMoveFromCombinations();

    AlgorithmResult Run();
};

#endif
