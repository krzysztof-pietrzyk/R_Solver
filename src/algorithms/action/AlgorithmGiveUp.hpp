#ifndef ALGORITHM_GIVE_UP_HPP
#define ALGORITHM_GIVE_UP_HPP

#include "AlgorithmAction.hpp"

class AlgorithmGiveUp : public AlgorithmAction
{
    public:

    AlgorithmGiveUp(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmGiveUp();

    protected:

    AlgorithmStatus Execution() override;
};

#endif
