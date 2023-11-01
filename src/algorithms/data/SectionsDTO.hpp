#ifndef SECTIONS_DTO_HPP
#define SECTIONS_DTO_HPP

// project includes
#include "../../utils/CachedVector.hpp"

// std includes

// forward declarations
struct GridDimensions;
class Section;


struct SectionsDTO
{
    CachedVector sections_origins;
    std::vector<Section> sections;

    SectionsDTO(GridDimensions dim);

    void Clear();
};

#endif
