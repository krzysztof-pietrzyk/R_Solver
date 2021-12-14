#ifndef GridView_hpp
#define GridView_hpp

#include "Grid.hpp"

class GridView
{
    public:

    GridView(Grid& grid);

    ~GridView();

    virtual void Display() = 0;

    protected:

    Grid& grid;
};

#endif
