#ifndef AlgorithmFactory_hpp
#define AlgorithmFactory_hpp

#include "Algorithm.hpp"
#include "AlgorithmLayerOne.hpp"
#include "AlgorithmSimpleCorners.hpp"

enum AlgorithmType
{
    ALGORITHM_LAYER_ONE,
    ALGORITHM_SIMPLE_CORNERS
};

class AlgorithmFactory
{
    public:

    static Algorithm* Create(AlgorithmType type, GridManager& grid);

    ~AlgorithmFactory();

    protected:

    AlgorithmFactory();
};

#endif
