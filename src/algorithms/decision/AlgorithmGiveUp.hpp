#ifndef ALGORITHM_GIVE_UP_HPP
#define ALGORITHM_GIVE_UP_HPP

#include "AlgorithmDecision.hpp"

class AlgorithmGiveUp : public AlgorithmDecision
{
    public:

    AlgorithmGiveUp(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmGiveUp();

    protected:

    AlgorithmStatus Execution() override;

    private:

    bool& D_is_lost;
};

#endif
