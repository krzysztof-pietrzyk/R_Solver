#include "ViewFactory.hpp"

ViewIf* ViewFactory::Create(ViewType type, GridAccessViewIf& grid)
{
    switch(type)
    {
        case ViewType::CONSOLE:
            return new ViewConsole(grid);
        default:
            throw std::invalid_argument("ERROR: ViewFactory::Create Attempting to create a non-existent View type!");
    }
}