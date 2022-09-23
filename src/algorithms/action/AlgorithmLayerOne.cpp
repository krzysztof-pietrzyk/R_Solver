#include "AlgorithmLayerOne.hpp"

AlgorithmLayerOne::AlgorithmLayerOne(GridManager& grid_, AlgorithmDataStorage& data_) : AlgorithmAction(grid_, data_) {}

AlgorithmLayerOne::~AlgorithmLayerOne() {}

AlgorithmStatus AlgorithmLayerOne::RunInternal()
{
    const unsigned int number_of_clicks_before = grid.left_click_counter + grid.right_click_counter;
    const unsigned int border_index_max = data.border_index;
    const std::vector<unsigned int>& border = data.GetBorder();

    // Go through each field on the broder
    for(size_t i = 0; i < border_index_max; i++)
    {
        const unsigned int border_field = border[i];
        const LayerOneFieldSignature field_signature = GetFieldSignature(border_field);
        CheckForSafeClicks(field_signature);
        CheckForMines(field_signature);
    }

    const unsigned int number_of_clicks_after = grid.left_click_counter + grid.right_click_counter;
    if(number_of_clicks_after > number_of_clicks_before) { return AlgorithmStatus::SUCCESS; }
    return AlgorithmStatus::NO_MOVES;
}

LayerOneFieldSignature AlgorithmLayerOne::GetFieldSignature(const unsigned int border_field) const
{
    unsigned char flags_count = 0;
    unsigned char not_visible_count = 0;
    // Count flags and covered fields around the border field
    for(const unsigned int& neighbor_field : grid.neighbors[border_field])
    {
        if(grid.is_flag[neighbor_field]) flags_count++;
        else if(!grid.is_visible[neighbor_field]) not_visible_count++;
    }
    LayerOneFieldSignature result;
    result.field = border_field;
    result.flags_count = flags_count;
    result.not_visible_count = not_visible_count;
    result.field_value = grid.FieldValue(border_field);
    return result;
}

void AlgorithmLayerOne::CheckForSafeClicks(const LayerOneFieldSignature signature) const
{
    // If there are already enough flags...
    if(signature.field_value != signature.flags_count) { return; }
    for(const unsigned int& neighbor_field : grid.neighbors[signature.field])
    {
        if(!grid.is_flag[neighbor_field] && !grid.is_visible[neighbor_field])
        {
            // ...left click on all remaining covered fields
            grid.LeftClick(neighbor_field);
        }
    }
}

void AlgorithmLayerOne::CheckForMines(const LayerOneFieldSignature signature) const
{
    // If the remaining covered fields exactly account for missing flags...
    if(signature.field_value != signature.flags_count + signature.not_visible_count) { return; }
    for(const unsigned int& neighbor_field : grid.neighbors[signature.field])
    {
        if(!grid.is_flag[neighbor_field] && !grid.is_visible[neighbor_field])
        {
            // ...right click on all remaining covered fields
            grid.RightClick(neighbor_field);
        }
    }
}
