#ifndef GridGenerator_hpp
#define GridGenerator_hpp

#include "Grid.hpp"

class GridGenerator
{
    public:

    GridGenerator(Grid& grid);

    ~GridGenerator();

    virtual void Generate() = 0;

    protected:

    Grid& grid;

    unsigned int* empty_template;

    unsigned int* safe_fields;
    unsigned int safe_fields_index;
    
    unsigned int* generated_mines;
    unsigned int generated_mines_index;
};

#endif