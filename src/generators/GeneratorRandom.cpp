#include "GeneratorRandom.hpp"

GeneratorRandom::GeneratorRandom(GridAccessGeneratorIf& grid_, GeneratorRandomType type)
    : GeneratorInternal(grid_)
{
    generator_type = type;
    ValidateGridDimensions();
    CreateTemplate();
    previous_starting_field = starting_field;
}

GeneratorRandom::~GeneratorRandom()
{

}

void GeneratorRandom::SetStartingField(uint32_t new_starting_field)
{
    GeneratorCommon::SetStartingField(new_starting_field);
    if(new_starting_field != previous_starting_field)
    {
        previous_starting_field = new_starting_field;
        CreateTemplate();
    }
}

void GeneratorRandom::ValidateGridDimensions()
{
    switch(generator_type)
    {
        case UNSAFE:
            break;
        case GUARANTEED_SAFE:
            if(grid.GetSize() <= grid.GetTotalMines())
            {
                throw std::runtime_error("ERROR: GeneratorRandom::ValidateGridDimensions() Invalid grid dimensions for GUARANTEED_SAFE.");
            }
            break;
        case GUARANTEED_OPENING:
            if(grid.GetSize() - grid.GetTotalMines() <= 8U)
            {
                throw std::runtime_error("ERROR: GeneratorRandom::ValidateGridDimensions() Invalid grid dimensions for GUARANTEED_OPENING.");
            }
            break;
        default:
            break;
    }
}

void GeneratorRandom::CreateTemplate()
{
    switch(generator_type)
    {
        case UNSAFE:
            CreateUnsafeTemplate();
            break;
        case GUARANTEED_SAFE:
            CreateSafeTemplate();
            break;
        case GUARANTEED_OPENING:
            CreateGuaranteedOpeningTemplate();
            break;
        default:
            CreateUnsafeTemplate();
            break;
    }
    current_max = current_template.size();
}

void GeneratorRandom::CreateUnsafeTemplate()
{
    current_template = std::vector<uint32_t>(grid.GetSize(), 0U);
    for(uint32_t i = 0U; i < grid.GetSize(); i++)
    {
        current_template[i] = i;
    }
}

void GeneratorRandom::CreateSafeTemplate()
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
}

void GeneratorRandom::CreateGuaranteedOpeningTemplate()
{
    const std::vector<uint32_t>& starting_field_neighbors = grid.GetFieldNeighbors(starting_field);
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
}

void GeneratorRandom::GenerateMinePositions()
{
    uint32_t poll_index = 0;
    uint32_t random_field = 0;
    current_max = current_template.size();

    CopyTemplateToWorkingVector();

    for(size_t i = 0; i < grid.GetTotalMines(); i++)
    {
        // Get random poll_index between 0 and current_max
        poll_index = RandomNumberGenerator::GetRandom() % current_max;
        // generated_safe_fields[poll_index] is the next generated mine
        random_field = generated_safe_fields[poll_index];
        generated_mine_fields.Add(random_field);
        // Move the last value in generated_safe_fields to generated_safe_fields[poll_index] and decrement current_max
        generated_safe_fields[poll_index] = generated_safe_fields[--current_max];
    }
}

void GeneratorRandom::CopyTemplateToWorkingVector()
{
    const size_t current_template_size = current_template.size();
    for(size_t i = 0; i < current_template_size; i++)
    {
        generated_safe_fields[i] = current_template[i];
    }
}
