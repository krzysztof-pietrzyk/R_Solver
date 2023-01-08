#ifndef ALGORITHM_REFRESH_SUBSEGMENTS_HPP
#define ALGORITHM_REFRESH_SUBSEGMENTS_HPP

#include "../Algorithm.hpp"

class AlgorithmRefreshSubsegments : public Algorithm
{
    public:

    AlgorithmRefreshSubsegments(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmRefreshSubsegments();

    AlgorithmStatus Execution() override;

    protected:

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

    void FindPossibleValuesForSubsegment(SubsegmentData& subsegment_data) const;

    uint32_t NChooseK(const uint32_t n, const uint32_t k) const;

    private:

    std::vector<std::vector<SubsegmentData>>& D_subsegments;
    std::vector<bool>& D_is_subsegment;
    std::vector<uint32_t>& D_subsegments_cache;
    uint32_t& D_subsegments_cache_index;
};

#endif
