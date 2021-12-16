#ifndef AlgorithmRefreshFace_hpp
#define AlgorithmRefreshFace_hpp

#include "Algorithm.hpp"
#include "AlgorithmDataStorage.hpp"

class AlgorithmRefreshFace : public Algorithm
{
    public:

    AlgorithmRefreshFace(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmRefreshFace();

    bool Run();

    protected:

    AlgorithmDataStorage& data;
};

#endif