#ifndef AlgorithmSureMovesFromCombinations_hpp
#define AlgorithmSureMovesFromCombinations_hpp

#include "Algorithm.hpp"

class AlgorithmSureMovesFromCombinations : public Algorithm
{
    public:

    AlgorithmSureMovesFromCombinations(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmSureMovesFromCombinations();

    AlgorithmResult Run();
};

#endif
