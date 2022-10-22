#ifndef AlgorithmDataStorage_hpp
#define AlgorithmDataStorage_hpp

#include <vector>
#include <map>

#include "../grid/GridManager.hpp"
#include "Section.hpp"

struct SubsegmentData
{
    std::vector<unsigned int> fields;
    std::vector<unsigned char> possible_values;
    std::map<unsigned char, unsigned int> combinations_for_value;
    size_t total_possibilities;
    size_t current_possibility_id;
};

class AlgorithmDataStorage
{
    /*
    This class is used for storing all data which needs to be exchanged between algorithms.
    */
    public:

    unsigned int border_index;
    unsigned int border_last_visible_fields_index;
    std::vector<unsigned int> border;
    std::vector<bool> is_border;

    unsigned int sections_origins_index;
    std::vector<unsigned int> sections_origins;
    std::vector<bool> is_section_origin;
    std::vector<Section> sections;

    unsigned int segments_index;
    unsigned int segments_count;
    std::vector<unsigned int> segments;
    std::vector<unsigned int> segments_starting_indexes;
    std::vector<unsigned int> segments_l;

    // subsegments[segment_id][subsegment_id]
    // subsegments are parts of segments (section fields), which have exactly the same neighbors (section origins)
    // those subsegments can be used to optimize the combinations checking algorithm
    std::vector<std::vector<SubsegmentData>> subsegments;
    std::vector<bool> is_subsegment;
    std::vector<unsigned int> subsegments_cache;
    unsigned int subsegments_cache_index;

    std::vector<unsigned int> face;
    std::vector<bool> is_face;
    unsigned int face_index;
    std::vector<std::vector<unsigned int>> segments_face;

    std::vector<long double> factorial;
    std::vector<long double> factorial_reciprocal;

    // long double allows to count up to 10^4932 combinations
    // It should be enough for about 2000 independent segments multiplied together
    std::vector<long double> field_combinations;
    // number of combinations in which one remaining field is a mine (the same number for each remaining field)
    long double remaining_fields_combinations;
    long double total_combinations;

    AlgorithmDataStorage(GridManager& grid);

    ~AlgorithmDataStorage();

    void Clear();

    private:

    void PreCalculateFactorials(GridManager& grid);
};

#endif
