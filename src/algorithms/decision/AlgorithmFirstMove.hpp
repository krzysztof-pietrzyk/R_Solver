#ifndef ALGORITHM_FIRST_MOVE_HPP
#define ALGORITHM_FIRST_MOVE_HPP

#include "AlgorithmDecision.hpp"

class AlgorithmFirstMove : public AlgorithmDecision
{
    public:

    AlgorithmFirstMove(GridAccessPlayerIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmFirstMove();

    protected:

    uint32_t first_move_field;

    AlgorithmStatus Execution() override;

    private:

    static const uint32_t default_first_move_field;
};

#endif
