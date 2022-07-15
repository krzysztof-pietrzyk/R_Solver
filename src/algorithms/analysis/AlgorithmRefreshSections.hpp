#ifndef AlgorithmRefreshSections_hpp
#define AlgorithmRefreshSections_hpp

#include "../Algorithm.hpp"

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

    const unsigned int double_grid_width;
    std::vector<unsigned int> sections_hashes;

    void Clear();

    unsigned int GetHashBit(unsigned int difference);

    bool CheckHashUnique(unsigned int hash);
};

#endif
    