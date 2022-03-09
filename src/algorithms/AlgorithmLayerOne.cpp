#include "AlgorithmLayerOne.hpp"

AlgorithmLayerOne::AlgorithmLayerOne(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_), data(data_) {}

AlgorithmLayerOne::~AlgorithmLayerOne() {}

bool AlgorithmLayerOne::Run()
{
    const unsigned int number_of_clicks_before = grid.left_click_counter + grid.right_click_counter;
    const unsigned int border_index_max = data.border_index;
    unsigned char flags_count = 0;
    unsigned char not_visible_count = 0;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int border_field_temp = 0;
    unsigned char field_value_temp = 0;
    unsigned int neighbor_field = 0;

    unsigned int* border = data.border;

    for(i = 0; i < border_index_max; i++)
    {
        border_field_temp = border[i];
        flags_count = 0;
        not_visible_count = 0;
        for_grid_neighbors_of(border_field_temp)
        {
            neighbor_field = grid.neighbors[x];
            if(grid.is_flag[neighbor_field]) flags_count++;
            else if(!grid.is_visible[neighbor_field]) not_visible_count++;
        }
        field_value_temp = grid.FieldValue(border_field_temp);
        if(field_value_temp == flags_count)
        {
            for_grid_neighbors_of(border_field_temp)
            {
                neighbor_field = grid.neighbors[x];
                if(!grid.is_flag[neighbor_field] && !grid.is_visible[neighbor_field]) grid.LeftClick(neighbor_field);
            }
        }
        else if(field_value_temp == flags_count + not_visible_count)
        {
            for_grid_neighbors_of(border_field_temp)
            {
                neighbor_field = grid.neighbors[x];
                if(!grid.is_flag[neighbor_field] && !grid.is_visible[neighbor_field]) grid.RightClick(neighbor_field);
            }
        }
    }
    const unsigned int number_of_clicks_after = grid.left_click_counter + grid.right_click_counter;
    return number_of_clicks_after > number_of_clicks_before;
}
