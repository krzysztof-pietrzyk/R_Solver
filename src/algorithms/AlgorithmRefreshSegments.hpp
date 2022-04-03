#ifndef AlgorithmRefreshSegments_hpp
#define AlgorithmRefreshSegments_hpp

#include "Algorithm.hpp"
#include "AlgorithmDataStorage.hpp"

class AlgorithmRefreshSegments : public Algorithm
{
    public:

    AlgorithmRefreshSegments(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmRefreshSegments();

    bool Run();

    protected:

    AlgorithmDataStorage& data;

};

#endif
