#ifndef AlgorithmDataStorage_hpp
#define AlgorithmDataStorage_hpp

#include <vector>

#include "grid/GridManager.hpp"

#define MAX_SECTION_LENGTH 8
#define MAX_SECTION_NEIGHBORS 16

class AlgorithmDataStorage
{
    public:

    unsigned int border_index;
    unsigned int last_read_index_border;
    unsigned int last_read_index_border_flags;
    bool border_internal_indicator;
    std::vector<bool> is_border;
    std::vector<unsigned int> border_internal_0;
    std::vector<unsigned int> border_internal_1;

    unsigned int sections_origins_index;
    std::vector<unsigned int> sections_origins;
    std::vector<bool> is_section_origin;
    std::vector<unsigned int> sections;
    std::vector<unsigned char> sections_l;
    std::vector<unsigned char> sections_values;
    std::vector<unsigned int> sections_neighbors;
    std::vector<unsigned char> sections_neighbors_l;

    unsigned int segments_index;
    unsigned int segments_count;
    std::vector<unsigned int> segments;
    std::vector<unsigned int> segments_starting_indexes;
    std::vector<unsigned int> segments_l;

    AlgorithmDataStorage(GridManager& grid);

    ~AlgorithmDataStorage();

    std::vector<unsigned int>& GetBorder();

    void Clear();

};

#endif
