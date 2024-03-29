#ifndef ALGORITHM_FIRST_MOVE_HPP
#define ALGORITHM_FIRST_MOVE_HPP

// project includes
#include "AlgorithmAction.hpp"

// std includes

// forward declarations


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
