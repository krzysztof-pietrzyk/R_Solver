#ifndef AlgorithmOptimizedSegments_hpp
#define AlgorithmOptimizedSegments_hpp

#include "Algorithm.hpp"

class AlgorithmOptimizedSegments : public Algorithm
{
    public:

    AlgorithmOptimizedSegments(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmOptimizedSegments();

    bool Run();

    protected:

    std::vector<bool> is_checked;
    std::vector<unsigned int> checked;
    unsigned int checked_index;
    // key: field position (section's neighbor), value: unique bit
    std::map<unsigned int, unsigned int> neighbors_bits;
    // key: neighborhood hash, value: vector of section fields' positions, which have the same hash
    std::map<unsigned int, std::vector<unsigned int>> section_neighborhood;

    void Clear();

    void UpdateNeighborsBits(unsigned int border_field);

    void UpdateSectionNeighborhood(unsigned int section_origin);

    void FindSegmentsToOptimize(unsigned int parent_segment);

    unsigned int GetNeighborhoodHash(unsigned int section_field);

    void FindPossibleValuesForSubsegment(OptimizedSegmentData& subsegment_data);

    unsigned int NChooseK(unsigned int n, unsigned int k);
};

#endif
