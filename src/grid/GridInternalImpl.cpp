#include "GridInternalImpl.hpp"

GridInternalImpl::GridInternalImpl(GridDimensions dimensions) : GridImpl(dimensions)
{
    chain_reaction_zeros = CachedVector(dimensions.size);
}

GridInternalImpl::~GridInternalImpl()
{

}


// GridAccessPlayerIf
PlayerActionResult GridInternalImpl::SetVisible(uint32_t field)
{
    if(visible_fields.Contains(field) || is_lost)
    {
        return PlayerActionResult::INCORRECT;
    }
    visible_fields.Add(field);
    if(mine_fields.Contains(field))
    {
        is_lost = true;
        return PlayerActionResult::INCORRECT;
    } 
    if(field_values[field] == 0U)
    {
        StartChainReactionAt(field);
        return PlayerActionResult::CORRECT;
    }
    return PlayerActionResult::CORRECT;
}

PlayerActionResult GridInternalImpl::SetFlag(uint32_t field)
{
    if(flagged_fields.Contains(field) || is_lost)
    {
        // GridInternalImpl does not allow to remove flags - it's never needed
        return PlayerActionResult::INCORRECT;
    }
    flagged_fields.Add(field);
    return PlayerActionResult::CORRECT;
}

void GridInternalImpl::StartChainReactionAt(uint32_t field)
{
    // Return if called on a non-zero field
    if(GetFieldValue(field) != 0U) { return; }

    chain_reaction_zeros.Clear();
    chain_reaction_zeros.Add(field);
    // chain_reaction_zeros.CurrentIndex() may increase while the loop is being executed
    for(size_t i = 0U; i < chain_reaction_zeros.CurrentIndex(); i++)
    {
        uint32_t current_zero = chain_reaction_zeros[i];
        HandleChainReactionAt(current_zero);
    }
}

void GridInternalImpl::HandleChainReactionAt(uint32_t field)
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
