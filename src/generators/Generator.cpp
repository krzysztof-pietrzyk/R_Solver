#include "Generator.hpp"

Generator::Generator(GridGeneratorIf& grid_) : grid(grid_), grid_dim(grid_.GetDimensions())
{
    LOGGER(LogLevel::INIT) << "Generator";
    SetStartingField(0);
}

Generator::~Generator()
{
    
}

void Generator::SetStartingField(uint32_t new_starting_field)
{
    LOGGER_ASSERT(new_starting_field < grid_dim.size, "Generator::SetStartingField - out of bounds")
    starting_field = new_starting_field;
}
