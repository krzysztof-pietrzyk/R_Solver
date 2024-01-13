// implemented header
#include "SubsegmentsDTO.hpp"

// project includes
#include "Subsegment.hpp"
#include "../../grid/GridDimensions.hpp"

// std includes


SubsegmentsDTO::SubsegmentsDTO(GridDimensions dim)
{
    subsegments_cache = CachedVector(dim.size);
    subsegments = std::vector<std::vector<Subsegment>>();
}

void SubsegmentsDTO::Clear()
{
    subsegments_cache.Clear();
    subsegments.clear();
}
