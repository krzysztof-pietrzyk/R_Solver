#ifndef AlgorithmOptimizedSegments_hpp
#define AlgorithmOptimizedSegments_hpp

#include "Algorithm.hpp"

class AlgorithmOptimizedSegments : public Algorithm
{
    public:

    AlgorithmOptimizedSegments(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmOptimizedSegments();

    bool Run();
};

#endif
