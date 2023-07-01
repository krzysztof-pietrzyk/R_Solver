#include "GeneratorRandomSafe.hpp"

GeneratorRandomSafe::GeneratorRandomSafe(GridAccessGeneratorIf& grid_)
    : GeneratorRandom(grid_)
{
    ValidateGridDimensions();
    CreateTemplate();
}

GeneratorRandomSafe::~GeneratorRandomSafe()
{

}

void GeneratorRandomSafe::ValidateGridDimensions()
{
    const uint32_t minimum_safe_fields = 1U;
    if(grid.GetSize() - grid.GetTotalMines() < minimum_safe_fields)
    {
        throw std::runtime_error("ERROR: GeneratorRandomSafe::ValidateGridDimensions() Invalid grid dimensions.");
    }
}

void GeneratorRandomSafe::CreateTemplate()
{
    current_template = std::vector<uint32_t>(grid.GetSize() - 1U, 0U);
    uint32_t index = 0U;
    for(uint32_t i = 0U; i < grid.GetSize(); i++)
    {
        if(i == starting_field)
        {
            continue;
        }
        current_template[index++] = i;
    }
    current_max = current_template.size();
}
