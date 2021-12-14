#include "GridViewFactory.hpp"

GridViewFactory::GridViewFactory() {}

GridViewFactory::~GridViewFactory() {}

GridView* GridViewFactory::Create(GridViewType type, Grid& grid)
{
    switch(type)
    {
        case GRID_VIEW_CONSOLE:
            return new GridViewConsole(grid);
        default:
            return NULL;
    }
}