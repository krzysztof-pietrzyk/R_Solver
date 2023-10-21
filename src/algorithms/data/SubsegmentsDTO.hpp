#ifndef SUBSEGMENTS_DTO_HPP
#define SUBSEGMENTS_DTO_HPP

#include <vector>
#include <cstdint>

#include "../../grid/GridDimensions.hpp"
#include "../../utils/CachedVector.hpp"

#include "Subsegment.hpp"

struct SubsegmentsDTO
{
    CachedVector subsegments_cache;
    // subsegments[segment_id][subsegment_id]
    // subsegments are parts of segments (section fields), which have exactly the same neighbors (section origins)
    // those subsegments can be used to optimize the combinations checking algorithm
    std::vector<std::vector<Subsegment>> subsegments;

    SubsegmentsDTO(GridDimensions dim);

    void Clear();
};

#endif
