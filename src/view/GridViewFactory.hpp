#ifndef GRID_VIEW_FACTORY_HPP
#define GRID_VIEW_FACTORY_HPP

#include <stdexcept>

#include "GridView.hpp"
#include "GridViewConsole.hpp"

enum GridViewType
{
    GRID_VIEW_CONSOLE,
    GRID_VIEW_FILE
};

class GridViewFactory
{
    public:

    static GridView* Create(GridViewType type, Grid& grid);

    ~GridViewFactory();

    protected:

    GridViewFactory();

};

#endif
