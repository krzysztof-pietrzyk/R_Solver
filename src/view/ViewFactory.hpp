#ifndef VIEW_FACTORY_HPP
#define VIEW_FACTORY_HPP

#include <stdexcept>

#include "ViewIf.hpp"
#include "ViewConsole.hpp"

enum ViewType
{
    VIEW_CONSOLE,
    VIEW_FILE
};

class ViewFactory
{
    public:

    ViewFactory() = delete;

    ~ViewFactory() = delete;

    static ViewIf* Create(ViewType type, GridAccessViewIf& grid);
};

#endif
