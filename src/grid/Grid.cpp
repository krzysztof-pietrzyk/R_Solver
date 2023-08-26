#include "Grid.hpp"

Grid::Grid(const GridDimensions dimensions) : dimensions(dimensions)
{
    LOGGER(LogLevel::INIT) << "Grid";
    VerifyDimensions(dimensions);
    mine_fields = CachedVector(dimensions.size);
    flagged_fields = CachedVector(dimensions.size);
    visible_fields = CachedVector(dimensions.size);
    field_values = std::vector<uint8_t>(dimensions.size);
    field_types_to_display = std::vector<FieldType>(dimensions.size);
    neighbors = std::vector<std::vector<uint32_t>>(dimensions.size);
    for(size_t i = 0U; i < dimensions.size; i++)
    {
        neighbors[i] = std::vector<uint32_t>();
    }
    FindNeighborsOfAllFields();
    is_lost = false;
}

Grid::~Grid()
{

}

// GridAccessCommonIf
GridDimensions Grid::GetDimensions() const 
{
    return dimensions;
}

uint16_t Grid::GetWidth() const
{
    return dimensions.width;
}

uint16_t Grid::GetHeight() const
{
    return dimensions.height;
}

uint32_t Grid::GetSize() const
{
    return dimensions.size;
}

uint32_t Grid::GetTotalMines() const
{
    return dimensions.mines;
}

uint32_t Grid::GetTotalSafeFields() const
{
    return dimensions.safe;
}

const std::vector<uint32_t>& Grid::GetNeighbors(uint32_t field) const
{
    return neighbors.at(field);
}

// GridAccessPlayerIf
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

bool Grid::IsLost() const
{
    return is_lost;
}

bool Grid::IsWon() const
{
    return !is_lost && visible_fields.Index() == dimensions.safe;
}

void Grid::GiveUp()
{
    is_lost = true;
}

// GridAccessGeneratorIf
void Grid::SetMineFields(const CachedVector& new_mine_fields)
{
    CachedVector::CopyFromTo(new_mine_fields, mine_fields);
}

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

void Grid::Reset()
{
    flagged_fields.Clear();
    visible_fields.Clear();
    is_lost = false;
}

// GridAccessViewIf
const std::vector<FieldType>& Grid::GetFieldTypesToDisplay()
{
    for(size_t i = 0U; i < dimensions.size; i++)
    {
        field_types_to_display[i] = GetFieldType(i);
    }
    return field_types_to_display;
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
    for(uint32_t i = 0U; i < dimensions.size; i++)
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

FieldType Grid::GetFieldType(uint32_t field)
{
    if(is_lost)
    {
        return GetFieldTypeLostGrid(field);
    }
    return GetFieldTypeOngoingGrid(field);
}

FieldType Grid::GetFieldTypeLostGrid(uint32_t field)
{
    bool is_mine = mine_fields.Contains(field);
    bool is_flag = flagged_fields.Contains(field);
    bool is_visible = visible_fields.Contains(field);
    if(is_flag)
    {
        if(!is_mine)
        {
            return FieldType::F_FLAGGED_INCORRECTLY;
        }
        return FieldType::F_FLAGGED;
    }
    if(is_mine)
    {
        if(is_visible)
        {
            return FieldType::F_MINE_EXPLODED;
        }
        return FieldType::F_MINE_UNFLAGGED;
    }
    if(!is_visible)
    {
        return FieldType::F_COVERED;
    }
    return GetFieldTypeNumbered(field);
}

FieldType Grid::GetFieldTypeOngoingGrid(uint32_t field)
{
    bool is_flag = flagged_fields.Contains(field);
    bool is_visible = visible_fields.Contains(field);
    if(is_flag)
    {
        return FieldType::F_FLAGGED;
    }
    if(!is_visible)
    {
        return FieldType::F_COVERED;
    }
    return GetFieldTypeNumbered(field);
}

FieldType Grid::GetFieldTypeNumbered(uint32_t field)
{
    uint8_t field_value = GetFieldValue(field);
    switch(field_value)
    {
        case 0U:
            return FieldType::F_0;
        case 1U:
            return FieldType::F_1;
        case 2U:
            return FieldType::F_2;
        case 3U:
            return FieldType::F_3;
        case 4U:
            return FieldType::F_4;
        case 5U:
            return FieldType::F_5;
        case 6U:
            return FieldType::F_6;
        case 7U:
            return FieldType::F_7;
        case 8U:
            return FieldType::F_8;
        default:
            LOGGER_THROW("Grid::GetFieldTypeNumbered - impossible field value");
    }
}
