#ifndef GRID_VIEW_HPP
#define GRID_VIEW_HPP

#include "../grid/Grid.hpp"

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
