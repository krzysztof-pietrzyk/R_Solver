#ifndef VIEW_FACTORY_HPP
#define VIEW_FACTORY_HPP

#include "ViewIf.hpp"
#include "ViewConsole.hpp"

enum class ViewType
{
    CONSOLE,
    FILE
};

class ViewFactory
{
    public:

    ViewFactory() = delete;

    ~ViewFactory() = delete;

    static ViewIf* Create(ViewType type, GridAccessViewIf& grid);
};

#endif
