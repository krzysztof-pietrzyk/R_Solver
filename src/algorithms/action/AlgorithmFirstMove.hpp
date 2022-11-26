#ifndef ALGORITHM_FIRST_MOVE_HPP
#define ALGORITHM_FIRST_MOVE_HPP

#include "AlgorithmAction.hpp"

class AlgorithmFirstMove : public AlgorithmAction
{
    public:

    AlgorithmFirstMove(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmFirstMove();

    protected:

    uint32_t first_move_field;

    void RunInternal() override;

    private:

    static const uint32_t default_first_move_field;
};

#endif
