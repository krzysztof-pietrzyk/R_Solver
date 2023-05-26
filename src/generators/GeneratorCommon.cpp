#include "GeneratorCommon.hpp"

GeneratorCommon::GeneratorCommon(GridAccessGeneratorIf& grid_) : grid(grid_)
{
    SetStartingField(0);
}

GeneratorCommon::~GeneratorCommon()
{
    
}

void GeneratorCommon::SetStartingField(uint32_t new_starting_field)
{
    if(new_starting_field >= grid.GetSize())
    {
        throw std::runtime_error("ERROR: GeneratorCommon::SetStartingField out of bounds.");
    }
    starting_field = new_starting_field;
}
