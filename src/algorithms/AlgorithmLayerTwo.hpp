#ifndef AlgorithmLayerTwo_hpp
#define AlgorithmLayerTwo_hpp

#include "Algorithm.hpp"
#include "AlgorithmDataStorage.hpp"

class AlgorithmLayerTwo : public Algorithm
{
    public:

    AlgorithmLayerTwo(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmLayerTwo();

    bool Run();

    protected:

    AlgorithmDataStorage& data;

};

#endif