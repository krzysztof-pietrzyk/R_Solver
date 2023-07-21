#include "GeneratorRandomGuaranteedOpening.hpp"

GeneratorRandomGuaranteedOpening::GeneratorRandomGuaranteedOpening(GridAccessGeneratorIf& grid_)
    : GeneratorRandom(grid_)
{
    LOGGER(LOG_INIT) << "GeneratorRandomGuaranteedOpening";
    ValidateGridDimensions();
    CreateTemplate();
}

GeneratorRandomGuaranteedOpening::~GeneratorRandomGuaranteedOpening()
{

}

void GeneratorRandomGuaranteedOpening::ValidateGridDimensions()
{
    const uint32_t minimum_safe_fields = 9U;
    if(grid.GetSize() - grid.GetTotalMines() < minimum_safe_fields)
    {
        throw std::runtime_error("ERROR: GeneratorRandomGuaranteedOpening::ValidateGridDimensions() Invalid grid dimensions.");
    }
}

void GeneratorRandomGuaranteedOpening::CreateTemplate()
{
    const std::vector<uint32_t>& starting_field_neighbors = grid.GetNeighbors(starting_field);
    const uint32_t starting_field_neighbors_num = starting_field_neighbors.size();
    current_template = std::vector<uint32_t>(grid.GetSize() - starting_field_neighbors_num - 1U, 0U);
    uint32_t index = 0U;
    for(uint32_t i = 0U; i < grid.GetSize(); i++)
    {
        if(i == starting_field || std::find(starting_field_neighbors.begin(), starting_field_neighbors.end(), i) != starting_field_neighbors.end())
        {
            continue;
        }
        current_template[index++] = i;
    }
    current_max = current_template.size();
}
