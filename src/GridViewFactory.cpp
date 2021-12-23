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
            throw std::invalid_argument("ERROR: Attempting to create a non-existent GridView type!");
    }
}