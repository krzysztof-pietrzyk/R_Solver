#ifndef GridInternalGenerator_hpp
#define GridInternalGenerator_hpp

#include "grid/GridSelfGenerated.hpp"
#include "utils/Buffer.hpp"
#include "utils/ValueTable.hpp"

#include "GridGenerator.hpp"

class GridInternalGenerator : public GridGenerator
{
    public:

    GridInternalGenerator(GridSelfGenerated& grid_);

    ~GridInternalGenerator();

    protected:

    GridSelfGenerated& grid;

    ValueTable empty_template;
    ValueTable safe_fields;
    Buffer generated_mines;
};

#endif