// implemented header
#include "Grid.hpp"

// project includes
#include "../utils/Logger.hpp"

// std includes


Grid::Grid(GridDimensions dimensions) : dimensions(dimensions)
{
    LOGGER(LogLevel::INIT) << "Grid";
    VerifyDimensions(dimensions);
    flagged_fields = CachedVector(dimensions.size);
    visible_fields = CachedVector(dimensions.size);
    field_values = std::vector<uint8_t>(dimensions.size);
    neighbors = std::vector<std::vector<uint32_t>>(dimensions.size);
    for(size_t i = 0U; i < dimensions.size; ++i)
    {
        neighbors[i] = std::vector<uint32_t>();
    }
    FindNeighborsOfAllFields();
    is_lost = false;
}

Grid::~Grid()
{

}

// GridCommonIf
GridDimensions Grid::GetDimensions() const 
{
    return dimensions;
}

const std::vector<uint32_t>& Grid::GetNeighbors(uint32_t field) const
{
    return neighbors.at(field);
}

bool Grid::IsLost() const
{
    return is_lost;
}

bool Grid::IsWon() const
{
    return !is_lost && visible_fields.Index() == dimensions.safe;
}

// GridAlgorithmIf
const CachedVector& Grid::GetVisibleFields() const
{
    return visible_fields;
}

const CachedVector& Grid::GetFlaggedFields() const
{
    return flagged_fields;
}

uint8_t Grid::GetFieldValue(uint32_t field) const
{
    LOGGER_ASSERT(CheckVisible(field), "Grid::GetFieldValue attempting to read value of a covered field!");
    return field_values[field];
}

// GridGeneratorIf
void Grid::SetFlaggedFields(const CachedVector& new_flagged_fields)
{
    CachedVector::CopyFromTo(new_flagged_fields, flagged_fields);
}

void Grid::SetVisibleFields(const CachedVector& new_visible_fields)
{
    CachedVector::CopyFromTo(new_visible_fields, visible_fields);
}

void Grid::SetFieldValues(const std::vector<uint8_t>& new_field_values)
{
    std::copy(new_field_values.begin(), new_field_values.end(), field_values.begin());
}

void Grid::SetLost(bool new_is_lost)
{
    is_lost = new_is_lost;
}

void Grid::Reset()
{
    flagged_fields.Clear();
    visible_fields.Clear();
    is_lost = false;
}

bool Grid::CheckVisible(uint32_t field) const
{
    return visible_fields.Contains(field);
}

// Private
void Grid::VerifyDimensions(GridDimensions dim) const
{
    LOGGER_ASSERT(dim.mines < dim.size, "Grid::VerifyDimensions - Too many mines in grid.");
    LOGGER_ASSERT(dim.mines >= 1U, "Grid::VerifyDimensions - Too few mines in grid.");
    LOGGER_ASSERT(dim.height <= 1024U && dim.width <= 1024U, "Grid::VerifyDimensions - Grid too big.");
    LOGGER_ASSERT(dim.height > 0U && dim.width > 0U, "Grid::VerifyDimensions - Grid too small.");
}

void Grid::FindNeighborsOfAllFields()
{
    // Only called once in constructor. The neighbors addresses never change
    uint16_t column;
    uint16_t row;
    for(uint32_t i = 0U; i < dimensions.size; ++i)
    {
        // For each field, list the neighbors
        column = i % dimensions.width;
        row = i / dimensions.width;
        if(column - 1 >= 0 && row - 1 >= 0)                neighbors[i].push_back(i - 1 - dimensions.width);  // Upper Left
        if(row - 1 >= 0)                                   neighbors[i].push_back(i - dimensions.width);      // Upper Middle
        if(column + 1 < dimensions.width && row - 1 >= 0)  neighbors[i].push_back(i + 1 - dimensions.width);  // Upper Right
        if(column - 1 >= 0)                                neighbors[i].push_back(i - 1);                     // Middle Left
        if(column + 1 < dimensions.width)                  neighbors[i].push_back(i + 1);                     // Middle Right
        if(column - 1 >= 0 && row + 1 < dimensions.height) neighbors[i].push_back(i - 1 + dimensions.width);  // Bottom Left
        if(row + 1 < dimensions.height)                    neighbors[i].push_back(i + dimensions.width);      // Bottom Middle
        if(column + 1 < dimensions.width && row + 1 < dimensions.height) neighbors[i].push_back(i + 1 + dimensions.width);  // Bottom Right
    }
}
