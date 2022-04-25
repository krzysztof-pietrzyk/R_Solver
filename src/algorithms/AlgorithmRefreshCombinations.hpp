#ifndef AlgorithmRefreshCombinations_hpp
#define AlgorithmRefreshCombinations_hpp

#include "Algorithm.hpp"

class AlgorithmRefreshCombinations : public Algorithm
{
    public:

    AlgorithmRefreshCombinations(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmRefreshCombinations();

    bool Run();
};

#endif
