// implemented header
#include "GeneratorRandom.hpp"

// project includes
#include "RandomNumberGenerator.hpp"

// std includes


GeneratorRandom::GeneratorRandom(GridGeneratorIf& grid_)
    : GeneratorInternal(grid_)
{
    LOGGER(LogLevel::INIT) << "GeneratorRandom";
    previous_starting_field = Generator::starting_field;
}

GeneratorRandom::~GeneratorRandom()
{

}

void GeneratorRandom::SetStartingField(uint32_t new_starting_field)
{
    Generator::SetStartingField(new_starting_field);
    if(new_starting_field != previous_starting_field)
    {
        previous_starting_field = new_starting_field;
        CreateTemplate();
    }
}

void GeneratorRandom::GenerateMinePositions()
{
    uint32_t poll_index = 0;
    uint32_t random_field = 0;
    current_max = current_template.size();

    CopyTemplateToWorkingVector();

    for(size_t i = 0; i < grid_dim.mines; i++)
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
