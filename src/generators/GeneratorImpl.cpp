#include "GeneratorImpl.hpp"

GeneratorImpl::GeneratorImpl(GridAccessGeneratorIf& grid_) : grid(grid_)
{
    LOGGER(LOG_INIT) << "GeneratorImpl";
    SetStartingField(0);
}

GeneratorImpl::~GeneratorImpl()
{
    
}

void GeneratorImpl::SetStartingField(uint32_t new_starting_field)
{
    if(new_starting_field >= grid.GetSize())
    {
        throw std::runtime_error("ERROR: GeneratorImpl::SetStartingField out of bounds.");
    }
    starting_field = new_starting_field;
}
