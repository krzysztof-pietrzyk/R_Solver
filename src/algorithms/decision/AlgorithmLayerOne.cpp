// implemented header
#include "AlgorithmLayerOne.hpp"

// project includes
#include "LayerOneFieldSignature.hpp"

// std includes


AlgorithmLayerOne::AlgorithmLayerOne(GridAlgorithmIf& grid_, AlgorithmDataTransfer& data_)
    : AlgorithmDecision(grid_, data_),
    border_dto(data_.border_dto)
{
    LOGGER(LogLevel::INIT) << "AlgorithmLayerOne";
    algorithm_type = AlgorithmType::LAYER_ONE;
}

AlgorithmLayerOne::~AlgorithmLayerOne() {}

AlgorithmStatus AlgorithmLayerOne::Execution()
{
    const uint32_t border_index_max = border_dto.index;

    // Go through each field on the broder
    for(size_t i = 0; i < border_index_max; ++i)
    {
        const uint32_t border_field = border_dto.border[i];
        const LayerOneFieldSignature field_signature = GetFieldSignature(border_field);
        CheckForSafeClicks(field_signature);
        CheckForMines(field_signature);
    }

    return AlgorithmStatus::NO_STATUS;
}

LayerOneFieldSignature AlgorithmLayerOne::GetFieldSignature(const uint32_t border_field) const
{
    uint8_t flags_count = 0;
    uint8_t not_visible_count = 0;
    // Count flags and covered fields around the border field
    const std::vector<uint32_t>& neighbor_fields = grid.GetNeighbors(border_field);
    for(const uint32_t& neighbor_field : neighbor_fields)
    {
        if(flagged.Contains(neighbor_field))       { ++flags_count; }
        else if(!visible.Contains(neighbor_field)) { ++not_visible_count; }
    }
    LayerOneFieldSignature result;
    result.field = border_field;
    result.flags_count = flags_count;
    result.not_visible_count = not_visible_count;
    result.field_value = grid.GetFieldValue(border_field);
    return result;
}

void AlgorithmLayerOne::CheckForSafeClicks(const LayerOneFieldSignature& signature)
{
    // If there are already enough flags...
    if(signature.field_value != signature.flags_count) { return; }
    const std::vector<uint32_t>& neighbor_fields = grid.GetNeighbors(signature.field);
    for(const uint32_t& neighbor_field : neighbor_fields)
    {
        if(!flagged.Contains(neighbor_field) && !visible.Contains(neighbor_field))
        {
            // ...left click on all remaining covered fields
            QueueAction(neighbor_field, PlayerAction::LEFT_CLICK);
        }
    }
}

void AlgorithmLayerOne::CheckForMines(const LayerOneFieldSignature& signature)
{
    // If the remaining covered fields exactly account for missing flags...
    if(signature.field_value != signature.flags_count + signature.not_visible_count) { return; }
    const std::vector<uint32_t>& neighbor_fields = grid.GetNeighbors(signature.field);
    for(const uint32_t& neighbor_field : neighbor_fields)
    {
        if(!flagged.Contains(neighbor_field) && !visible.Contains(neighbor_field))
        {
            // ...right click on all remaining covered fields
            QueueAction(neighbor_field, PlayerAction::RIGHT_CLICK);
        }
    }
}
