#ifndef AlgorithmCombinationsLeastRisky_hpp
#define AlgorithmCombinationsLeastRisky_hpp

#include "AlgorithmAction.hpp"

class AlgorithmCombinationsLeastRisky : public AlgorithmAction
{
    public:

    AlgorithmCombinationsLeastRisky(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmCombinationsLeastRisky();

    protected:

    AlgorithmStatus RunInternal();
};

#endif
