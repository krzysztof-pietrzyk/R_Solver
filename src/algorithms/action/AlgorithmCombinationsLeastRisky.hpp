#ifndef ALGORITHM_COMBINATIONS_LEAST_RISKY_HPP
#define ALGORITHM_COMBINATIONS_LEAST_RISKY_HPP

#include "AlgorithmAction.hpp"

class AlgorithmCombinationsLeastRisky : public AlgorithmAction
{
    public:

    AlgorithmCombinationsLeastRisky(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmCombinationsLeastRisky();

    protected:

    AlgorithmStatus Execution() override;

    uint32_t FindSafestField() const;

    const BigNum max_combinations;
};

#endif
