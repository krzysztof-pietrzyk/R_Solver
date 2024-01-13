#ifndef VIEW_FACTORY_HPP
#define VIEW_FACTORY_HPP

// project includes
#include "ViewIf.hpp"
#include "ViewType.hpp"

// std includes

// forward declarations
class GridViewIf;


class ViewFactory
{
    public:

    ViewFactory() = delete;

    ~ViewFactory() = delete;

    static ViewIf* Create(ViewType type, GridViewIf& grid);
};

#endif
