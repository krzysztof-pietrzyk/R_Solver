#include "GeneratorRandomUnsafe.hpp"

GeneratorRandomUnsafe::GeneratorRandomUnsafe(GridAccessGeneratorIf& grid_)
    : GeneratorRandom(grid_)
{
    LOGGER(LOG_INIT) << "GeneratorRandomUnsafe";
    ValidateGridDimensions();
    CreateTemplate();
}

GeneratorRandomUnsafe::~GeneratorRandomUnsafe()
{

}

void GeneratorRandomUnsafe::ValidateGridDimensions()
{
    return;
}

void GeneratorRandomUnsafe::CreateTemplate()
{
    current_template = std::vector<uint32_t>(grid.GetSize(), 0U);
    for(uint32_t i = 0U; i < grid.GetSize(); i++)
    {
        current_template[i] = i;
    }
    current_max = current_template.size();
}
