#include "SubsegmentsDTO.hpp"

SubsegmentsDTO::SubsegmentsDTO(GridDimensions dim)
{
    subsegments_cache = CachedVector(dim.size);
    subsegments = std::vector<std::vector<Subsegment>>();
}
