#ifndef ALGORITHM_SIMPLE_ACTIONS_HPP
#define ALGORITHM_SIMPLE_ACTIONS_HPP

#include "AlgorithmAction.hpp"

class AlgorithmSimpleActions : public AlgorithmAction
{
    public:

    AlgorithmSimpleActions(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmSimpleActions();

    protected:

    AlgorithmStatus Execution() override;

    private:

    ActionsDTO& actions_dto;
};

#endif
