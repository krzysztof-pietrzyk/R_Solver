#ifndef ALGORITHM_GIVE_UP_HPP
#define ALGORITHM_GIVE_UP_HPP

#include "AlgorithmAction.hpp"

class AlgorithmGiveUp : public AlgorithmAction
{
    public:

    AlgorithmGiveUp(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmGiveUp();

    protected:

    void RunInternal() override;

    private:

    bool& D_is_lost;
};

#endif
