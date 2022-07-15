#ifndef AlgorithmSafestMoveFromCombinations_hpp
#define AlgorithmSafestMoveFromCombinations_hpp

#include "AlgorithmAction.hpp"

class AlgorithmSafestMoveFromCombinations : public AlgorithmAction
{
    public:

    AlgorithmSafestMoveFromCombinations(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmSafestMoveFromCombinations();

    protected:

    AlgorithmResult RunInternal();
};

#endif
