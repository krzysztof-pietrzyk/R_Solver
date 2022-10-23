#ifndef AlgorithmRefreshCombinations_hpp
#define AlgorithmRefreshCombinations_hpp

#include "../Algorithm.hpp"

enum FieldCombinationState
{
    FCS_UNASSIGNED,
    FCS_MINE,
    FCS_SAFE
};

class AlgorithmRefreshCombinations : public Algorithm
{
    public:

    AlgorithmRefreshCombinations(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmRefreshCombinations();

    AlgorithmStatus Run();

    protected:

    std::vector<FieldCombinationState> field_states;
    std::vector<unsigned int> choice_stack;
    std::vector<unsigned int> segment_of_choice_stack;
    std::vector<unsigned int> modifications_stack;
    unsigned int current_segment_mine_count;
    unsigned int remaining_mines;
    unsigned int remaining_fields;
    std::vector<std::vector<unsigned int>> mine_counts_in_segment;
    std::vector<size_t> current_mine_count_id_in_segment;

    // segments_combinations - vector id: segment number, key: mine count within the segment
    // value: number of possible mine combinations with that mine count for that segment
    std::vector<std::map<unsigned int, long double>> segments_combinations;
    // field_combinations_temp - vector id: field position, key: given mine count within entire segment
    // value: number of combinations, in which a mine appears on that field for given mine count of this segment
    std::vector<std::map<unsigned int, long double>> field_combinations_temp;

    void Clear();

    void FindCombinationsForSegment(unsigned int segment_id);

    void ClearStatesInSegment(unsigned int segment_id);

    long double ApplySubsegmentsCombination(std::vector<SubsegmentData>& subsegments_ref);

    void FindCombinationsForFixedSubsegments(const unsigned int segment_id, const long double combination_multiplier);

    void FindRemainingSectionValue(const Section& section, char& section_value, char& section_length) const;

    bool RevertSegmentHeadToLastChoice(size_t& segment_head);

    void TransitionFieldStateForward(const unsigned int section_field, const size_t current_segment_head, char& remaining_section_value, char& remaining_section_length);

    void ApplyCurrentCombinationAsValid(const unsigned int segment_id, const long double combination_multiplier);

    bool NextSubsegmentsCombination(std::vector<SubsegmentData>& subsegments_ref) const;

    void MergeAllSegmentsCombinations();

    void CachePossibleSegmentsMineCounts();

    unsigned int GetTotalMineCountOfSegmentCombination() const;

    void MergeCurrentSegmentsMineCountCombination(const unsigned int segments_combination_mine_count);

    bool NextSegmentsMineCountCombination();
};

#endif
