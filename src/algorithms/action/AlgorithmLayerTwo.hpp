#ifndef AlgorithmLayerTwo_hpp
#define AlgorithmLayerTwo_hpp

#include "AlgorithmAction.hpp"

class AlgorithmLayerTwo : public AlgorithmAction
{
    /*
    "Layer Two" algorithm implements the medium difficulty player strategy.
    It makes all safe decisions which can be made by considering pairs of neighboring numbered fields.
    */
    public:

    AlgorithmLayerTwo(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmLayerTwo();

    protected:

    AlgorithmResult RunInternal();
};

#endif