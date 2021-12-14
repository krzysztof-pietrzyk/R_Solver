#ifndef AlgorithmLayerOne_hpp
#define AlgorithmLayerOne_hpp

#include "Algorithm.hpp"

class AlgorithmLayerOne : public Algorithm
{
    public:

    AlgorithmLayerOne(GridManager& grid_);

    ~AlgorithmLayerOne();

    bool Run();
};

#endif
