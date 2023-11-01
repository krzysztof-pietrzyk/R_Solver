// implemented header
#include "ViewFactory.hpp"

// project includes
#include "ViewConsole.hpp"
#include "../utils/Logger.hpp"

// std includes


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
