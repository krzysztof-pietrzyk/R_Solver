#ifndef ALGORITHM_SEGMENTS_HPP
#define ALGORITHM_SEGMENTS_HPP

// project includes
#include "AlgorithmAnalysis.hpp"

// std includes

// forward declarations


class AlgorithmSegments : public AlgorithmAnalysis
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

    AlgorithmSegments(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmSegments();

    protected:

    AlgorithmStatus Execution() override;

    private:

    SectionsDTO& sections_dto;
    SegmentsDTO& segments_dto;
    
    std::vector<uint32_t> fields_to_check;
    uint32_t fields_to_check_index;
    std::vector<bool> is_checked;

    void Clear();

    void ChainReactionFromField(uint32_t field);
};

#endif
