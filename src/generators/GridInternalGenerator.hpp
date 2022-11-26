#ifndef GRID_INTERNAL_GENERATOR_HPP
#define GRID_INTERNAL_GENERATOR_HPP

#include <vector>

#include "../grid/GridSelfGenerated.hpp"

#include "GridGenerator.hpp"

class GridInternalGenerator : public GridGenerator
{
    public:

    GridInternalGenerator(GridSelfGenerated& grid_);

    ~GridInternalGenerator();

    protected:

    GridSelfGenerated& grid;

    std::vector<uint32_t> empty_template;

    std::vector<uint32_t> safe_fields;
    uint32_t safe_fields_index;
    
    std::vector<uint32_t> generated_mines;
    uint32_t generated_mines_index;
};

#endif
