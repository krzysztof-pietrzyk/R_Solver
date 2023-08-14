#include "Generator.hpp"

Generator::Generator(GridAccessGeneratorIf& grid_) : grid(grid_)
{
    LOGGER(LogLevel::INIT) << "Generator";
    SetStartingField(0);
}

Generator::~Generator()
{
    
}

void Generator::SetStartingField(uint32_t new_starting_field)
{
    LOGGER_ASSERT(new_starting_field < grid.GetSize(), "Generator::SetStartingField - out of bounds")
    starting_field = new_starting_field;
}
