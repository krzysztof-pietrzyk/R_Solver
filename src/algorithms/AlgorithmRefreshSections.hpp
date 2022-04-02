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
    const unsigned int double_grid_width;
    std::vector<unsigned int> sections_hashes;

    unsigned int GetHashBit(unsigned int difference);

    bool CheckHashUnique(unsigned int hash);
};

#endif
    