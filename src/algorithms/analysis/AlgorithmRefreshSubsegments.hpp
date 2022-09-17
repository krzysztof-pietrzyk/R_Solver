#ifndef AlgorithmRefreshSubsegments_hpp
#define AlgorithmRefreshSubsegments_hpp

#include "../Algorithm.hpp"

class AlgorithmRefreshSubsegments : public Algorithm
{
    public:

    AlgorithmRefreshSubsegments(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmRefreshSubsegments();

    AlgorithmStatus Run();

    protected:

    std::vector<bool> is_checked;
    std::vector<unsigned int> checked;
    unsigned int checked_index;
    // key: field position (section's neighbor), value: unique bit
    std::map<unsigned int, unsigned int> neighbors_bits;
    // key: neighborhood hash, value: vector of section fields' positions, which have the same hash
    std::map<unsigned int, std::vector<unsigned int>> section_neighborhood;

    void Clear();

    void UpdateNeighborsBits(const unsigned int border_field);

    void UpdateSectionNeighborhood(const unsigned int section_origin);

    void FindSegmentsToOptimize(const unsigned int parent_segment) const;

    unsigned int GetNeighborhoodHash(const unsigned int section_field);

    void FindPossibleValuesForSubsegment(SubsegmentData& subsegment_data) const;

    unsigned int NChooseK(const unsigned int n, const unsigned int k) const;
};

#endif
