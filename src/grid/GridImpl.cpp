#include "GridImpl.hpp"

GridImpl::GridImpl(const GridDimensions dimensions) : dimensions(dimensions)
{
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

GridImpl::~GridImpl()
{

}

// GridAccessCommonIf
GridDimensions GridImpl::GetDimensions() const 
{
    return dimensions;
}

uint16_t GridImpl::GetWidth() const
{
    return dimensions.width;
}

uint16_t GridImpl::GetHeight() const
{
    return dimensions.height;
}

uint32_t GridImpl::GetSize() const
{
    return dimensions.size;
}

uint32_t GridImpl::GetTotalMines() const
{
    return dimensions.mines;
}

uint32_t GridImpl::GetTotalSafeFields() const
{
    return dimensions.safe;
}

const std::vector<uint32_t>& GridImpl::GetFieldNeighbors(uint32_t field)
{
    return neighbors[field];
}

// GridAccessPlayerIf
const CachedVector& GridImpl::GetVisibleFields() const
{
    return visible_fields;
}

const CachedVector& GridImpl::GetFlaggedFields() const
{
    return flagged_fields;
}

uint8_t GridImpl::GetFieldValue(uint32_t field)
{
    if(visible_fields.Contains(field))
    {
        return field_values[field];
    }
    throw std::runtime_error("ERROR: GridImpl::GetFieldValue attempting to read value of a covered field!");
}

bool GridImpl::IsLost()
{
    return is_lost;
}

bool GridImpl::IsWon()
{
    return !is_lost && visible_fields.CurrentIndex() == dimensions.safe;
}

// GridAccessGeneratorIf
void GridImpl::SetMineFields(const CachedVector& new_mine_fields)
{
    CachedVector::CopyFromTo(new_mine_fields, mine_fields);
}

void GridImpl::SetFlaggedFields(const CachedVector& new_flagged_fields)
{
    CachedVector::CopyFromTo(new_flagged_fields, flagged_fields);
}

void GridImpl::SetVisibleFields(const CachedVector& new_visible_fields)
{
    CachedVector::CopyFromTo(new_visible_fields, visible_fields);
}

void GridImpl::SetFieldValues(const std::vector<uint8_t>& new_field_values)
{
    std::copy(new_field_values.begin(), new_field_values.end(), field_values.begin());
}

void GridImpl::ClearFlaggedFields()
{
    flagged_fields.Clear();
}

void GridImpl::ClearVisibleFields()
{
    visible_fields.Clear();
}


// GridAccessViewIf
const std::vector<FieldType>& GridImpl::GetFieldTypesToDisplay()
{
    for(size_t i = 0; i < dimensions.size; i++)
    {
        field_types_to_display[i] = GetFieldType(i);
    }
    return field_types_to_display;
}

// Private
void GridImpl::FindNeighborsOfAllFields()
{
    // Only called once in constructor. The neighbors addresses never change
    uint16_t column;
    uint16_t row;
    for(uint32_t i = 0; i < dimensions.size; i++)
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

FieldType GridImpl::GetFieldType(uint32_t field)
{
    if(is_lost)
    {
        return GetFieldTypeLostGrid(field);
    }
    return GetFieldTypeOngoingGrid(field);
}

FieldType GridImpl::GetFieldTypeLostGrid(uint32_t field)
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

FieldType GridImpl::GetFieldTypeOngoingGrid(uint32_t field)
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

FieldType GridImpl::GetFieldTypeNumbered(uint32_t field)
{
    uint8_t field_value = GetFieldValue(field);
    switch(field_value)
    {
        case 0:
            return FieldType::F_0;
        case 1:
            return FieldType::F_1;
        case 2:
            return FieldType::F_2;
        case 3:
            return FieldType::F_3;
        case 4:
            return FieldType::F_4;
        case 5:
            return FieldType::F_5;
        case 6:
            return FieldType::F_6;
        case 7:
            return FieldType::F_7;
        case 8:
            return FieldType::F_8;
        default:
            std::runtime_error("ERROR: GridImpl::GetFieldTypeNumbered impossible field value!");
            return FieldType::UNHANDLED_TYPE;
    }
}
