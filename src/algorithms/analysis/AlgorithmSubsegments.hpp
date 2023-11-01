#ifndef ALGORITHM_SUBSEGMENTS_HPP
#define ALGORITHM_SUBSEGMENTS_HPP

// project includes
#include "AlgorithmAnalysis.hpp"

// std includes

// forward declarations


class AlgorithmSubsegments : public AlgorithmAnalysis
{
    public:

    AlgorithmSubsegments(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmSubsegments();

    protected:

    AlgorithmStatus Execution() override;

    private:

    SectionsDTO& sections_dto;
    SegmentsDTO& segments_dto;
    SubsegmentsDTO& subsegments_dto;

    std::vector<bool> is_checked;
    std::vector<uint32_t> checked;
    uint32_t checked_index;
    // key: field position (section's neighbor), value: unique bit
    std::map<uint32_t, uint32_t> neighbors_bits;
    // key: neighborhood hash, value: vector of section fields' positions, which have the same hash
    std::map<uint32_t, std::vector<uint32_t>> section_neighborhood;

    void Clear();

    void UpdateNeighborsBits(const uint32_t border_field);

    void UpdateSectionNeighborhood(const uint32_t section_origin);

    void FindSegmentsToOptimize(const uint32_t parent_segment) const;

    uint32_t GetNeighborhoodHash(const uint32_t section_field);

    void FindPossibleValuesForSubsegment(Subsegment& subsegment_data) const;

    uint32_t NChooseK(const uint32_t n, const uint32_t k) const;
};

#endif
