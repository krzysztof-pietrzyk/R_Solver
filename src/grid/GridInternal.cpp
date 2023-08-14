#include "GridInternal.hpp"

GridInternal::GridInternal(GridDimensions dimensions) : Grid(dimensions)
{
    LOGGER(LogLevel::INIT) << "GridInternal";
    chain_reaction_zeros = CachedVector(dimensions.size);
}

GridInternal::~GridInternal()
{

}

// GridAccessCommonIf
GridHash GridInternal::GetHash() const
{
    return GridHash(mine_fields);
}

// GridAccessPlayerIf
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

void GridInternal::StartChainReactionAt(uint32_t field)
{
    // Return if called on a non-zero field
    if(GetFieldValue(field) != 0U) { return; }

    chain_reaction_zeros.Clear();
    chain_reaction_zeros.Add(field);
    // chain_reaction_zeros.Index() may increase while the loop is being executed
    for(size_t i = 0U; i < chain_reaction_zeros.Index(); i++)
    {
        uint32_t current_zero = chain_reaction_zeros[i];
        HandleChainReactionAt(current_zero);
    }
}

void GridInternal::HandleChainReactionAt(uint32_t field)
{
    for(const uint32_t& current_neighbor : neighbors[field])
    {
        if(visible_fields.Contains(current_neighbor)) { continue; }
        visible_fields.Add(current_neighbor);
        if(GetFieldValue(current_neighbor) == 0U && !chain_reaction_zeros.Contains(current_neighbor))
        {
            chain_reaction_zeros.Add(current_neighbor);
        }
    }
}
