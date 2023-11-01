// implemented header
#include "GeneratorRandomSafe.hpp"

// project includes

// std includes


const uint32_t GeneratorRandomSafe::minimum_safe_fields = 1U;

GeneratorRandomSafe::GeneratorRandomSafe(GridGeneratorIf& grid_)
    : GeneratorRandom(grid_)
{
    LOGGER(LogLevel::INIT) << "GeneratorRandomSafe";
    ValidateGridDimensions();
    CreateTemplate();
}

GeneratorRandomSafe::~GeneratorRandomSafe()
{

}

void GeneratorRandomSafe::ValidateGridDimensions()
{
    bool grid_valid = grid_dim.size - grid_dim.mines >= minimum_safe_fields;
    LOGGER_ASSERT(grid_valid, "GeneratorRandomSafe::ValidateGridDimensions - Invalid grid dimensions");
}

void GeneratorRandomSafe::CreateTemplate()
{
    current_template = std::vector<uint32_t>(grid_dim.size - 1U, 0U);
    uint32_t index = 0U;
    for(uint32_t i = 0U; i < grid_dim.size; i++)
    {
        if(i == starting_field)
        {
            continue;
        }
        current_template[index++] = i;
    }
    current_max = current_template.size();
    forced_safe_fields = std::vector<uint32_t>(minimum_safe_fields, 0U);
    forced_safe_fields[0] = starting_field;
}
