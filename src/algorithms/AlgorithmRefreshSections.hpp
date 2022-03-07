#ifndef AlgorithmRefreshSections_hpp
#define AlgorithmRefreshSections_hpp

#include "Algorithm.hpp"
#include "AlgorithmDataStorage.hpp"

class AlgorithmRefreshSections : public Algorithm
{
    public:

    AlgorithmRefreshSections(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmRefreshSections();

    bool Run();

    protected:

    AlgorithmDataStorage& data;
};

#endif
    