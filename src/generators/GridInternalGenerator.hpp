#ifndef GridInternalGenerator_hpp
#define GridInternalGenerator_hpp

#include "GridGenerator.hpp"
#include "GridSelfGenerated.hpp"

class GridInternalGenerator : public GridGenerator
{
    public:

    GridInternalGenerator(GridSelfGenerated& grid_);

    ~GridInternalGenerator();

    protected:

    GridSelfGenerated& grid;

    unsigned int* empty_template;

    unsigned int* safe_fields;
    unsigned int safe_fields_index;
    
    unsigned int* generated_mines;
    unsigned int generated_mines_index;
};

#endif