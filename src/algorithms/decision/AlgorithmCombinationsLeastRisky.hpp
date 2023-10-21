#ifndef ALGORITHM_COMBINATIONS_LEAST_RISKY_HPP
#define ALGORITHM_COMBINATIONS_LEAST_RISKY_HPP

#include "AlgorithmDecision.hpp"

class AlgorithmCombinationsLeastRisky : public AlgorithmDecision
{
    public:

    AlgorithmCombinationsLeastRisky(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmCombinationsLeastRisky();

    protected:

    AlgorithmStatus Execution() override;

    private:

    FaceDTO& face_dto;
    CombinationsDTO& combinations_dto;

    uint32_t FindSafestField() const;

    const BigNum max_combinations;
};

#endif
