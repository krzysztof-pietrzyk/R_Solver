#ifndef AlgorithmRefreshSections_hpp
#define AlgorithmRefreshSections_hpp

#include "../Algorithm.hpp"

#include <algorithm>

#define MAX_ALLOWED_GRID_SIZE 1048576

class AlgorithmRefreshSections : public Algorithm
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

    AlgorithmRefreshSections(GridManager& grid_, AlgorithmDataStorage& data_);

    ~AlgorithmRefreshSections();

    AlgorithmStatus Run();

    protected:

    std::vector<unsigned int> sections_hashes;

    void Clear();

    void AnalyzeSection(const unsigned int border_field);

    void AnalyzeSectionField(const unsigned int border_field, const unsigned int border_field_neighbor, Section& current_section);

    void AnalyzeSectionNeighbor(const unsigned int border_field, const unsigned int section_neighbor, Section& current_section) const;

    void SaveSectionData(const unsigned int border_field, Section& current_section) const;

    unsigned int GetHashBit(unsigned int difference) const;

    bool CheckHashUnique(unsigned int hash) const;

    unsigned char section_value_temp;
    unsigned int current_section_hash;

    const unsigned int diff_bit_20;
    const unsigned int diff_bit_21;
    const unsigned int diff_bit_22;
    const unsigned int diff_bit_23;
    const unsigned int diff_bit_24;
    const unsigned int diff_bit_25;
    const unsigned int diff_bit_26;
    const unsigned int diff_bit_27;
    const unsigned int diff_bit_28;
    const unsigned int diff_bit_29;
    const unsigned int diff_bit_30;
    const unsigned int diff_bit_31;

    private:

    unsigned int& D_sections_origins_index;
    std::vector<unsigned int>& D_sections_origins;
    std::vector<bool>& D_is_section_origin;
    std::vector<Section>& D_sections;
};

#endif
    