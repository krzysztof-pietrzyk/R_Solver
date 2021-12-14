#ifndef GridViewFactory_hpp
#define GridViewFactory_hpp

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