#ifndef ALGORITHM_GIVE_UP_HPP
#define ALGORITHM_GIVE_UP_HPP

// project includes
#include "AlgorithmAction.hpp"

// std includes

// forward declarations


class AlgorithmGiveUp : public AlgorithmAction
{
    public:

    AlgorithmGiveUp(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmGiveUp();

    protected:

    AlgorithmStatus Execution() override;
};

#endif
