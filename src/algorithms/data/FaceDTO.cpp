// implemented header
#include "FaceDTO.hpp"

// project includes
#include "../../grid/GridDimensions.hpp"

// std includes


FaceDTO::FaceDTO(GridDimensions dim)
{
    face = CachedVector(dim.size);
    segments_face = std::vector<std::vector<uint32_t>>(dim.mines, std::vector<uint32_t>());
}
