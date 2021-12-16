#ifndef AlgorithmRefreshBorder_hpp
#define AlgorithmRefreshBorder_hpp

#include "Algorithm.hpp"
#include "AlgorithmDataStorage.hpp"

class AlgorithmRefreshBorder : public Algorithm
{
    public:

    AlgorithmRefreshBorder(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmRefreshBorder();

    bool Run();

    protected:

    AlgorithmDataStorage& data;
};

#endif
