#ifndef FACE_DTO_HPP
#define FACE_DTO_HPP

#include <vector>
#include <cstdint>

#include "../../grid/GridDimensions.hpp"
#include "../../utils/CachedVector.hpp"

struct FaceDTO
{
    CachedVector face;
    std::vector<std::vector<uint32_t>> segments_face;

    FaceDTO(GridDimensions dim);
};

#endif
