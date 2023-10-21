#ifndef ALGORITHM_COMBINATIONS_SAFE_MOVES_HPP
#define ALGORITHM_COMBINATIONS_SAFE_MOVES_HPP

#include "AlgorithmDecision.hpp"

class AlgorithmCombinationsSafeMoves : public AlgorithmDecision
{
    public:

    AlgorithmCombinationsSafeMoves(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmCombinationsSafeMoves();

    protected:

    AlgorithmStatus Execution() override;

    private:

    FaceDTO& face_dto;
    CombinationsDTO& combinations_dto;
};

#endif
