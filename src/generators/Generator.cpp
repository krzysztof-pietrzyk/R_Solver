// implemented header
#include "Generator.hpp"

// project includes
#include "../utils/Logger.hpp"
#include "../utils/CachedVector.hpp"

// std includes


const uint8_t Generator::value_for_mine_fields = 9U;

Generator::Generator(GridGeneratorIf& grid_)
    : grid(grid_),
    grid_dim(grid_.GetDimensions())
{
    LOGGER(LogLevel::INIT) << "Generator";
    generated_mine_fields = CachedVector(grid_dim.size);
    generated_field_values = std::vector<uint8_t>(grid_dim.size, 0U);
    generated_visible_fields = CachedVector(grid_dim.size);
    generated_flagged_fields = CachedVector(grid_dim.size);
    generated_lost = false;
}

Generator::~Generator()
{
    
}

uint8_t Generator::CalculateFieldValue(uint32_t field)
{
    uint8_t current_field_value = 0U;
    const std::vector<uint32_t>& neighbors = grid.GetNeighbors(field);
    for(const uint32_t& current_neighbor : neighbors)
    {
        // Count how many mines are within each field's neighbors
        if(generated_mine_fields.Contains(current_neighbor))
        {
            ++current_field_value;
        }
    }
    return current_field_value;
}

void Generator::CalculateFieldValues()
{
    for(size_t field = 0; field < grid_dim.size; field++)
    {
        if(generated_mine_fields.Contains(field))
        {
            generated_field_values[field] = value_for_mine_fields;
            continue;
        }
        generated_field_values[field] = CalculateFieldValue(field);
    }
}

void Generator::CopyGeneratedDataToGrid()
{
    grid.SetMineFields(generated_mine_fields);
    grid.SetFieldValues(generated_field_values);
    grid.SetVisibleFields(generated_visible_fields);
    grid.SetFlaggedFields(generated_flagged_fields);
    grid.SetLost(generated_lost);
}

void Generator::ClearGeneratedVectors()
{
    generated_mine_fields.Clear();
    generated_field_values = std::vector<uint8_t>(grid_dim.size, 0U);
    generated_visible_fields.Clear();
    generated_flagged_fields.Clear();
}
