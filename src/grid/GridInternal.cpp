// implemented header
#include "GridInternal.hpp"

// project includes
#include "state/GridState.hpp"
#include "../utils/Logger.hpp"

// std includes


GridInternal::GridInternal(GridDimensions dimensions) : Grid(dimensions)
{
    LOGGER(LogLevel::INIT) << "GridInternal";
    mine_fields = CachedVector(dimensions.size);
    chain_reaction_zeros = CachedVector(dimensions.size);
    field_types_to_display = std::vector<FieldType>(dimensions.size);
}

GridInternal::~GridInternal()
{

}

// GridCommonIf
GridState GridInternal::GetState() const
{
    if(!IsLost() && !IsWon())
    {
        LOGGER(LogLevel::DEBUG2) << "GridInternal::GetState - Attempting to read GridState on an unfinished Grid";
    }
    return GridState(mine_fields, flagged_fields, visible_fields);
}

// GridAlgorithmIf
PlayerActionResult GridInternal::SetVisible(uint32_t field)
{
    if(visible_fields.Contains(field) || is_lost)
    {
        return PlayerActionResult::WASTED;
    }
    visible_fields.Add(field);
    if(mine_fields.Contains(field))
    {
        is_lost = true;
        return PlayerActionResult::EXPLODED;
    } 
    if(field_values[field] == 0U)
    {
        StartChainReactionAt(field);
    }
    return PlayerActionResult::CORRECT;
}

PlayerActionResult GridInternal::SetFlag(uint32_t field)
{
    if(flagged_fields.Contains(field) || is_lost)
    {
        // GridInternal does not allow to remove flags - it's never needed
        return PlayerActionResult::WASTED;
    }
    flagged_fields.Add(field);
    return PlayerActionResult::CORRECT;
}

void GridInternal::GiveUp()
{
    is_lost = true;
}

// GridGeneratorIf
void GridInternal::SetMineFields(const CachedVector& new_mine_fields)
{
    CachedVector::CopyFromTo(new_mine_fields, mine_fields);
}

// GridViewIf
const std::vector<FieldType>& GridInternal::GetFieldTypesToDisplay()
{
    for(size_t i = 0U; i < dimensions.size; ++i)
    {
        field_types_to_display[i] = GetFieldType(i);
    }
    return field_types_to_display;
}

void GridInternal::StartChainReactionAt(uint32_t field)
{
    // Return if called on a non-zero field
    if(GetFieldValue(field) != 0U)
    {
        return;
    }
    chain_reaction_zeros.Clear();
    chain_reaction_zeros.Add(field);
    // chain_reaction_zeros.Index() may increase while the loop is being executed
    for(size_t i = 0U; i < chain_reaction_zeros.Index(); ++i)
    {
        uint32_t current_zero = chain_reaction_zeros[i];
        HandleChainReactionAt(current_zero);
    }
}

void GridInternal::HandleChainReactionAt(uint32_t field)
{
    for(const uint32_t& current_neighbor : neighbors[field])
    {
        if(visible_fields.Contains(current_neighbor))
        {
            continue;
        }
        visible_fields.Add(current_neighbor);
        if(GetFieldValue(current_neighbor) == 0U && !chain_reaction_zeros.Contains(current_neighbor))
        {
            chain_reaction_zeros.Add(current_neighbor);
        }
    }
}

FieldType GridInternal::GetFieldType(uint32_t field)
{
    if(is_lost)
    {
        return GetFieldTypeLostGrid(field);
    }
    return GetFieldTypeOngoingGrid(field);
}

FieldType GridInternal::GetFieldTypeLostGrid(uint32_t field)
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

FieldType GridInternal::GetFieldTypeOngoingGrid(uint32_t field)
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

FieldType GridInternal::GetFieldTypeNumbered(uint32_t field)
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
            LOGGER_THROW("GridInternal::GetFieldTypeNumbered - impossible field value");
    }
}
