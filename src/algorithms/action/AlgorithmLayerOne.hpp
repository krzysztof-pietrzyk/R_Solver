#ifndef AlgorithmLayerOne_hpp
#define AlgorithmLayerOne_hpp

#include "AlgorithmAction.hpp"

class AlgorithmLayerOne : public AlgorithmAction
{
    /* 
    "Layer One" algorithm implements the most simple player strategy.
    It makes all safe decisions which can be made by considering one numbered field at a time.
    Example: If a 2 has exactly two covered fields around it, those two fields should be flagged.
    Example: If a 1 has exactly one flag around it, the remaining fields around it should be uncovered.
    */
    public:

    AlgorithmLayerOne(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmLayerOne();

    protected:

    AlgorithmStatus RunInternal();
};

#endif
