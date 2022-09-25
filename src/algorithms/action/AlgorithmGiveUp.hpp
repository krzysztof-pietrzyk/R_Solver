#ifndef AlgorithmGiveUp_hpp
#define AlgorithmGiveUp_hpp

#include "AlgorithmAction.hpp"

class AlgorithmGiveUp : public AlgorithmAction
{
    public:

    AlgorithmGiveUp(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmGiveUp();

    protected:

    void RunInternal();
};

#endif
