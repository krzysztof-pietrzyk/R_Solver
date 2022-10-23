#ifndef AlgorithmRefreshFace_hpp
#define AlgorithmRefreshFace_hpp

#include "../Algorithm.hpp"

class AlgorithmRefreshFace : public Algorithm
{
    public:

    AlgorithmRefreshFace(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmRefreshFace();

    AlgorithmStatus Run();

    protected:

    void Clear();
};

#endif
