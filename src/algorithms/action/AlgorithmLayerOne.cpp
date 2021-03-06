#include "AlgorithmLayerOne.hpp"

AlgorithmLayerOne::AlgorithmLayerOne(GridManager& grid_, AlgorithmDataStorage& data_) : AlgorithmAction(grid_, data_) {}

AlgorithmLayerOne::~AlgorithmLayerOne() {}

AlgorithmStatus AlgorithmLayerOne::RunInternal()
{
    const unsigned int number_of_clicks_before = grid.left_click_counter + grid.right_click_counter;
    const unsigned int border_index_max = data.border_index;
    unsigned char flags_count = 0;
    unsigned char not_visible_count = 0;
    size_t i = 0;

    const std::vector<unsigned int>& border = data.GetBorder();

    // Go through each field on the broder
    for(i = 0; i < border_index_max; i++)
    {
        const unsigned int border_field_temp = border[i];
        flags_count = 0;
        not_visible_count = 0;
        // Count flags and covered fields around the border field
        for(const unsigned int& neighbor_field : grid.neighbors[border_field_temp])
        {
            if(grid.is_flag[neighbor_field]) flags_count++;
            else if(!grid.is_visible[neighbor_field]) not_visible_count++;
        }
        const unsigned char field_value_temp = grid.FieldValue(border_field_temp);
        // If there are already enough flags, left click on all remaining covered fields
        if(field_value_temp == flags_count)
        {
            for(const unsigned int& neighbor_field : grid.neighbors[border_field_temp])
            {
                if(!grid.is_flag[neighbor_field] && !grid.is_visible[neighbor_field]) grid.LeftClick(neighbor_field);
            }
        }
        // If the remaining covered fields exactly account for missing flags, right click on them
        else if(field_value_temp == flags_count + not_visible_count)
        {
            for(const unsigned int& neighbor_field : grid.neighbors[border_field_temp])
            {
                if(!grid.is_flag[neighbor_field] && !grid.is_visible[neighbor_field]) grid.RightClick(neighbor_field);
            }
        }
    }
    const unsigned int number_of_clicks_after = grid.left_click_counter + grid.right_click_counter;

    if(number_of_clicks_after > number_of_clicks_before) { return AlgorithmStatus::SUCCESS; }
    return AlgorithmStatus::NO_MOVES;
}
