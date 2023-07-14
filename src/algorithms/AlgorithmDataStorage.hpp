#ifndef ALGORITHM_DATA_STORAGE_HPP
#define ALGORITHM_DATA_STORAGE_HPP

#include <vector>
#include <map>

#include "../grid/GridAccessPlayerIf.hpp"
#include "../utils/BigNum.hpp"
#include "Section.hpp"

struct SubsegmentData
{
    std::vector<uint32_t> fields;
    std::vector<uint8_t> possible_values;
    std::map<uint8_t, uint32_t> combinations_for_value;
    size_t total_possibilities;
    size_t current_possibility_id;
};

class AlgorithmDataStorage
{
    /*
    This class is used for storing all data which needs to be exchanged between algorithms.
    */
    public:

    uint32_t border_index;
    uint32_t border_last_visible_fields_index;
    std::vector<uint32_t> border;
    std::vector<bool> is_border;

    uint32_t sections_origins_index;
    std::vector<uint32_t> sections_origins;
    std::vector<bool> is_section_origin;
    std::vector<Section> sections;

    uint32_t segments_index;
    uint32_t segments_count;
    std::vector<uint32_t> segments;
    std::vector<uint32_t> segments_starting_indexes;
    std::vector<uint32_t> segments_l;

    // subsegments[segment_id][subsegment_id]
    // subsegments are parts of segments (section fields), which have exactly the same neighbors (section origins)
    // those subsegments can be used to optimize the combinations checking algorithm
    std::vector<std::vector<SubsegmentData>> subsegments;
    std::vector<bool> is_subsegment;
    std::vector<uint32_t> subsegments_cache;
    uint32_t subsegments_cache_index;

    std::vector<uint32_t> face;
    std::vector<bool> is_face;
    uint32_t face_index;
    std::vector<std::vector<uint32_t>> segments_face;

    std::vector<BigNum> factorial;
    std::vector<BigNum> factorial_reciprocal;

    std::vector<BigNum> field_combinations;
    // number of combinations in which one remaining field is a mine (the same number for each remaining field)
    BigNum remaining_fields_combinations;
    BigNum total_combinations;

    AlgorithmDataStorage(GridAccessPlayerIf& grid);

    ~AlgorithmDataStorage();

    void Clear();

    private:

    void PreCalculateFactorials(uint32_t grid_size);
};

#endif
