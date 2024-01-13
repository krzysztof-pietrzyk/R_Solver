#ifndef ALGORITHM_COMBINATIONS_LEAST_RISKY_HPP
#define ALGORITHM_COMBINATIONS_LEAST_RISKY_HPP

// project includes
#include "AlgorithmDecision.hpp"

// std includes

// forward declarations


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
