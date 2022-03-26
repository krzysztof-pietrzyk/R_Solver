#ifndef GridInternalGenerator_hpp
#define GridInternalGenerator_hpp

#include <vector>

#include "grid/GridSelfGenerated.hpp"

#include "GridGenerator.hpp"

class GridInternalGenerator : public GridGenerator
{
    public:

    GridInternalGenerator(GridSelfGenerated& grid_);

    ~GridInternalGenerator();

    protected:

    GridSelfGenerated& grid;

    std::vector<unsigned int> empty_template;

    std::vector<unsigned int> safe_fields;
    unsigned int safe_fields_index;
    
    std::vector<unsigned int> generated_mines;
    unsigned int generated_mines_index;
};

#endif