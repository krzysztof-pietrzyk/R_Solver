#ifndef AlgorithmRefreshSegments_hpp
#define AlgorithmRefreshSegments_hpp

#include "Algorithm.hpp"

class AlgorithmRefreshSegments : public Algorithm
{
    /*
    This algorithm gathers information about "segments".
    A segment is a set of sections overlapping with each other, usually in a form of a chain-like structure.
    See AlgorithmRefreshSegments for an explanation of what a section is.
    On the map there can be one or more segments. A segment can consist of one or more sections.
    The purpose of this analysis is to speed up the combination checking for the algorithms using this data later.
    Each segment can be analyzed separately for its possible combinations
    */
    public:

    AlgorithmRefreshSegments(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmRefreshSegments();

    bool Run();

    protected:
    
    std::vector<unsigned int> fields_to_check;
    unsigned int fields_to_check_index;
    std::vector<bool> is_checked;

    void Clear();

    void ChainReactionFromField(unsigned int field);

    // void DebugPrintSegments();

};

#endif
