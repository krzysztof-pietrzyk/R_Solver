#include "ViewFactory.hpp"

ViewIf* ViewFactory::Create(ViewType type, GridViewIf& grid)
{
    switch(type)
    {
        case ViewType::CONSOLE:
            return new ViewConsole(grid);
        default:
            LOGGER_THROW("ViewFactory::Create - unhandled ViewType");
    }
}