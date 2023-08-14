#include "Generator.hpp"

Generator::Generator(GridAccessGeneratorIf& grid_) : grid(grid_)
{
    LOGGER(LOG_INIT) << "Generator";
    SetStartingField(0);
}

Generator::~Generator()
{
    
}

void Generator::SetStartingField(uint32_t new_starting_field)
{
    if(new_starting_field >= grid.GetSize())
    {
        throw std::runtime_error("ERROR: Generator::SetStartingField out of bounds.");
    }
    starting_field = new_starting_field;
}
