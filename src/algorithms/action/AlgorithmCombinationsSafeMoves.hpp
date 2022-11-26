#ifndef ALGORITHM_COMBINATIONS_SAFE_MOVES_HPP
#define ALGORITHM_COMBINATIONS_SAFE_MOVES_HPP

#include "AlgorithmAction.hpp"

class AlgorithmCombinationsSafeMoves : public AlgorithmAction
{
    public:

    AlgorithmCombinationsSafeMoves(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmCombinationsSafeMoves();

    protected:

    void RunInternal() override;
};

#endif
