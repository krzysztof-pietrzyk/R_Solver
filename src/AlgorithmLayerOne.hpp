#ifndef AlgorithmLayerOne_hpp
#define AlgorithmLayerOne_hpp

#include "Algorithm.hpp"
#include "AlgorithmDataStorage.hpp"

class AlgorithmLayerOne : public Algorithm
{
    public:

    AlgorithmLayerOne(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmLayerOne();

    bool Run();

    protected:

    AlgorithmDataStorage& data;
};

#endif
