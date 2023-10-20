#include "FaceDTO.hpp"

FaceDTO::FaceDTO(GridDimensions dim)
{
    face = CachedVector(dim.size);
    segments_face = std::vector<std::vector<uint32_t>>(dim.mines, std::vector<uint32_t>());
}
