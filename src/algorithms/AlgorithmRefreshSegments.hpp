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
    
    std::vector<unsigned int> fields_to_check;
    unsigned int fields_to_check_index;
    std::vector<bool> is_checked;

    void Clear();

    void ChainReactionFromField(unsigned int field);

    // void DebugPrintSegments();

};

#endif
