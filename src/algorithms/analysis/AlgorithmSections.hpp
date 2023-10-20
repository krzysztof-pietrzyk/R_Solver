#ifndef ALGORITHM_SECTIONS_HPP
#define ALGORITHM_SECTIONS_HPP

#include "AlgorithmAnalysis.hpp"

#include <algorithm>

#define MAX_ALLOWED_GRID_SIZE 1048576

class AlgorithmSections : public AlgorithmAnalysis
{
    /*
    This algorithm gathers data about "sections".
    A section is a set of fields neighboring one border field (see AlgorithmRefresgBorder for explanation).
    Information gathered by this algorithm includes which covered fields are neighbors to
    each of the border fields, as well as which sections are overlapping.
    The "section" itself is the set of covered fields.
    The "section's origin" is the uncovered field those covered fields are neighboring.
    "section's neighbors" are the other sections' origins of which covered fields are overlapping given section.
    ONLY UNIQUE SECTIONS ARE SAVED IN THE DATA. A hashing method was designed for the purpose of efficiently comparing
    sections with each other in order to remove duplicates.
    */
    public:

    AlgorithmSections(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_);

    ~AlgorithmSections();

    protected:

    AlgorithmStatus Execution() override;

    private:

    std::vector<uint32_t> sections_hashes;
    uint8_t section_value_temp;
    uint32_t current_section_hash;

    const uint32_t diff_bit_20;
    const uint32_t diff_bit_21;
    const uint32_t diff_bit_22;
    const uint32_t diff_bit_23;
    const uint32_t diff_bit_24;
    const uint32_t diff_bit_25;
    const uint32_t diff_bit_26;
    const uint32_t diff_bit_27;
    const uint32_t diff_bit_28;
    const uint32_t diff_bit_29;
    const uint32_t diff_bit_30;
    const uint32_t diff_bit_31;

    void Clear();

    void AnalyzeSection(const uint32_t border_field);

    void AnalyzeSectionField(const uint32_t border_field, const uint32_t border_field_neighbor, Section& current_section);

    void AnalyzeSectionNeighbor(const uint32_t border_field, const uint32_t section_neighbor, Section& current_section) const;

    void SaveSectionData(const uint32_t border_field, Section& current_section) const;

    uint32_t GetHashBit(uint32_t difference) const;

    bool CheckHashUnique(uint32_t hash) const;
};

#endif
    