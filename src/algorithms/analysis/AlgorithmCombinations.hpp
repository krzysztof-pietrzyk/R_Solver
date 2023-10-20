#ifndef ALGORITHM_COMBINATIONS_HPP
#define ALGORITHM_COMBINATIONS_HPP

#include "../../statistics/collectors/StatisticsCollectorFailures.hpp"

#include "../Algorithm.hpp"

enum class FieldState
{
    UNASSIGNED,
    MINE,
    SAFE
};

class FailSafeException : public std::runtime_error
{
    public:

    FailSafeException() throw()
        : std::runtime_error("Too much data to process.")
    {

    }
};

class AlgorithmCombinations : public Algorithm
{
    public:

    AlgorithmCombinations(GridAlgorithmAnalysisIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmCombinations();

    AlgorithmStatus Execution() override;

    protected:

    std::vector<FieldState> field_states;
    std::vector<uint32_t> choice_stack;
    std::vector<uint32_t> segment_of_choice_stack;
    std::vector<uint32_t> modifications_stack;
    uint32_t current_segment_mine_count;
    uint32_t remaining_mines;
    uint32_t remaining_fields;
    std::vector<std::vector<uint32_t>> mine_counts_in_segment;
    std::vector<size_t> current_mine_count_id_in_segment;

    // segments_combinations - vector id: segment number, key: mine count within the segment
    // value: number of possible mine combinations with that mine count for that segment
    std::vector<std::map<uint32_t, BigNum>> segments_combinations;
    // field_combinations_temp - vector id: field position, key: given mine count within entire segment
    // value: number of combinations, in which a mine appears on that field for given mine count of this segment
    std::vector<std::map<uint32_t, BigNum>> field_combinations_temp;

    StatisticsCollectorFailures* statistics_failures;

    void Clear();

    void FindCombinationsForSegment(uint32_t segment_id);

    void ClearStatesInSegment(uint32_t segment_id);

    BigNum ApplySubsegmentsCombination(std::vector<Subsegment>& subsegments_ref);

    void FindCombinationsForFixedSubsegments(const uint32_t segment_id, const BigNum combination_multiplier);

    void FindRemainingSectionValue(const Section& section, int8_t& section_value, int8_t& section_length) const;

    bool RevertSegmentHeadToLastChoice(size_t& segment_head);

    void TransitionFieldStateForward(const uint32_t section_field, const size_t current_segment_head, int8_t& remaining_section_value, int8_t& remaining_section_length);

    void ApplyCurrentCombinationAsValid(const uint32_t segment_id, const BigNum combination_multiplier);

    bool NextSubsegmentsCombination(std::vector<Subsegment>& subsegments_ref) const;

    void MergeAllSegmentsCombinations();

    void CachePossibleSegmentsMineCounts();

    uint32_t GetTotalMineCountOfSegmentCombination() const;

    void MergeCurrentSegmentsMineCountCombination(const uint32_t segments_combination_mine_count);

    bool NextSegmentsMineCountCombination();

    private:

    std::vector<std::vector<Subsegment>>& D_subsegments;
    std::vector<BigNum>& D_field_combinations;
    BigNum& D_remaining_fields_combinations;
    BigNum& D_total_combinations;

    static const uint64_t fail_safe_permutation_threshold;
    static const uint64_t fail_safe_enumeration_threshold;
    uint64_t fail_safe_enumeration;
};

#endif
