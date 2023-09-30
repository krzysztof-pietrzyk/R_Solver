#ifndef ALGORITHM_SEGMENTS_HPP
#define ALGORITHM_SEGMENTS_HPP

#include "../Algorithm.hpp"

class AlgorithmSegments : public Algorithm
{
    /*
    This algorithm gathers information about "segments".
    A segment is a set of sections overlapping with each other, usually in a form of a chain-like structure.
    See AlgorithmSegments for an explanation of what a section is.
    On the map there can be one or more segments. A segment can consist of one or more sections.
    The purpose of this analysis is to speed up the combination checking for the algorithms using this data later.
    Each segment can be analyzed separately for its possible combinations
    */
    public:

    AlgorithmSegments(GridAccessPlayerIf& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmSegments();

    AlgorithmStatus Execution() override;

    protected:
    
    std::vector<uint32_t> fields_to_check;
    uint32_t fields_to_check_index;
    std::vector<bool> is_checked;

    void Clear();

    void ChainReactionFromField(uint32_t field);

    private:

    uint32_t& D_segments_index;
    uint32_t& D_segments_count;
    std::vector<uint32_t>& D_segments;
    std::vector<uint32_t>& D_segments_starting_indexes;
    std::vector<uint32_t>& D_segments_l;
};

#endif
