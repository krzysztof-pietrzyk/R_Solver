#ifndef ALGORITHM_GIVE_UP_HPP
#define ALGORITHM_GIVE_UP_HPP

#include "AlgorithmDecision.hpp"

class AlgorithmGiveUp : public AlgorithmDecision
{
    public:

    AlgorithmGiveUp(GridAlgorithmAnalysisIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmGiveUp();

    protected:

    AlgorithmStatus Execution() override;

    private:

    GridAlgorithmAnalysisIf& D_grid;
};

#endif
