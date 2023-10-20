#ifndef ALGORITHM_FIRST_MOVE_HPP
#define ALGORITHM_FIRST_MOVE_HPP

#include "AlgorithmAction.hpp"

class AlgorithmFirstMove : public AlgorithmAction
{
    public:

    AlgorithmFirstMove(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmFirstMove();

    protected:

    AlgorithmStatus Execution() override;

    private:

    static const uint32_t first_move_field;
};

#endif
