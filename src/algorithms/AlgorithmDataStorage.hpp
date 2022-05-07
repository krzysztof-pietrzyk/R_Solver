#ifndef AlgorithmDataStorage_hpp
#define AlgorithmDataStorage_hpp

#include <vector>
#include <map>

#include "grid/GridManager.hpp"

#define MAX_SECTION_LENGTH 8
#define MAX_SECTION_NEIGHBORS 16

struct OptimizedSegmentData
{
    std::vector<unsigned int> fields;
    std::vector<unsigned char> possible_values;
};

class AlgorithmDataStorage
{
    /*
    This class is used for storing all data which needs to be exchanged between algorithms.
    */
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

    // optimized_segments[segment_id][optimized_segment_id]
    std::vector<std::vector<OptimizedSegmentData>> optimized_segments;

    // segments_combinations - vector id: segment number, key: mine count within the segment
    // value: number of possible mine combinations with that mine count for that segment
    // border_combinations - vector id: field position, key: given mine count within entire segment
    // value: number of combinations, in which a mine appears on that field for given mine count of this segment
    // long double allows to count up to 10^4932 combinations
    // It should be enough for about 2000 independent segments multiplied together
    std::vector<std::map<unsigned int, long double>> segments_combinations;
    std::vector<std::map<unsigned int, long double>> border_combinations;

    AlgorithmDataStorage(GridManager& grid);

    ~AlgorithmDataStorage();

    std::vector<unsigned int>& GetBorder();

    void Clear();

};

#endif
