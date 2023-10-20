#ifndef SECTIONS_DTO_HPP
#define SECTIONS_DTO_HPP

#include <vector>
#include <cstdint>

#include "../../grid/GridDimensions.hpp"
#include "../../utils/CachedVector.hpp"

#include "Section.hpp"

struct SectionsDTO
{
    CachedVector sections_origins;
    std::vector<Section> sections;

    SectionsDTO(GridDimensions dim);

    void Clear();
};

#endif
