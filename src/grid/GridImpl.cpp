#include "GridImpl.hpp"

GridImpl::GridImpl(const GridDimensions dimensions) : dimensions(dimensions)
{
    LOGGER(LOG_INIT) << "GridImpl";
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

const std::vector<uint32_t>& GridImpl::GetNeighbors(uint32_t field) const
{
    return neighbors.at(field);
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

uint8_t GridImpl::GetFieldValue(uint32_t field) const
{
    if(visible_fields.Contains(field))
    {
        return field_values[field];
    }
    throw std::runtime_error("ERROR: GridImpl::GetFieldValue attempting to read value of a covered field!");
}

bool GridImpl::IsLost() const
{
    return is_lost;
}

bool GridImpl::IsWon() const
{
    return !is_lost && visible_fields.Index() == dimensions.safe;
}

void GridImpl::GiveUp()
{
    is_lost = true;
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

void GridImpl::Reset()
{
    flagged_fields.Clear();
    visible_fields.Clear();
    is_lost = false;
}

// GridAccessViewIf
const std::vector<FieldType>& GridImpl::GetFieldTypesToDisplay()
{
    for(size_t i = 0U; i < dimensions.size; i++)
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
            std::runtime_error("ERROR: GridImpl::GetFieldTypeNumbered impossible field value!");
            return FieldType::UNHANDLED_FIELD_TYPE;
    }
}
