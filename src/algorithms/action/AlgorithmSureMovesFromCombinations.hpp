#ifndef AlgorithmSureMovesFromCombinations_hpp
#define AlgorithmSureMovesFromCombinations_hpp

#include "AlgorithmAction.hpp"

class AlgorithmSureMovesFromCombinations : public AlgorithmAction
{
    public:

    AlgorithmSureMovesFromCombinations(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmSureMovesFromCombinations();

    protected:

    AlgorithmStatus RunInternal();
};

#endif
