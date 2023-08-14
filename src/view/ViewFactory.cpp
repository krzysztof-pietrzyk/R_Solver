#include "ViewFactory.hpp"

ViewIf* ViewFactory::Create(ViewType type, GridAccessViewIf& grid)
{
    switch(type)
    {
        case ViewType::CONSOLE:
            return new ViewConsole(grid);
        default:
            throw std::runtime_error("ViewFactory::Create - unhandled ViewType");
    }
}