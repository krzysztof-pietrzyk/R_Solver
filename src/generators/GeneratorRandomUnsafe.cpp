#include "GeneratorRandomUnsafe.hpp"

GeneratorRandomUnsafe::GeneratorRandomUnsafe(GridAccessGeneratorIf& grid_)
    : GeneratorRandom(grid_)
{
    LOGGER(LogLevel::INIT) << "GeneratorRandomUnsafe";
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
    current_template = std::vector<uint32_t>(grid_dim.size, 0U);
    for(uint32_t i = 0U; i < grid_dim.size; i++)
    {
        current_template[i] = i;
    }
    current_max = current_template.size();
}
