#ifndef AlgorithmCombinationsSafeMoves_hpp
#define AlgorithmCombinationsSafeMoves_hpp

#include "AlgorithmAction.hpp"

class AlgorithmCombinationsSafeMoves : public AlgorithmAction
{
    public:

    AlgorithmCombinationsSafeMoves(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmCombinationsSafeMoves();

    protected:

    void RunInternal();
};

#endif
