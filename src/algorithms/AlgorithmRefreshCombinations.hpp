#ifndef AlgorithmRefreshCombinations_hpp
#define AlgorithmRefreshCombinations_hpp

#include "Algorithm.hpp"

enum FieldCombinationState
{
    FCS_UNASSIGNED,
    FCS_FREE_CHOICE, 
    FCS_MINE,
    FCS_SAFE, 
    FCS_OPTIMIZED
};

class AlgorithmRefreshCombinations : public Algorithm
{
    public:

    AlgorithmRefreshCombinations(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmRefreshCombinations();

    bool Run();

    protected:

    std::vector<FieldCombinationState> states;

};

#endif
