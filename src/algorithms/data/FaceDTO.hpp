#ifndef FACE_DTO_HPP
#define FACE_DTO_HPP

// project includes
#include "../../utils/CachedVector.hpp"

// std includes

// forward declarations
class GridDimensions;


struct FaceDTO
{
    CachedVector face;
    std::vector<std::vector<uint32_t>> segments_face;

    FaceDTO(GridDimensions dim);
};

#endif
