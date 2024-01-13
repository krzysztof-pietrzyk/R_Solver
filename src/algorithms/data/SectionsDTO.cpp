// implemented header
#include "SectionsDTO.hpp"

// project includes
#include "Section.hpp"
#include "../../grid/GridDimensions.hpp"

// std includes


SectionsDTO::SectionsDTO(GridDimensions dim)
{
    sections_origins = CachedVector(dim.size);
    sections = std::vector<Section>(dim.size, Section());
}

void SectionsDTO::Clear()
{
    const size_t sections_origins_index = sections_origins.Index();
    for(size_t i = 0; i < sections_origins_index; ++i)
    {
        sections[i].fields_index = 0;
        sections[i].neighbors_index = 0;
    }
    sections_origins.Clear();
}
