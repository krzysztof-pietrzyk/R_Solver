#include "AlgorithmLayerOne.hpp"

AlgorithmLayerOne::AlgorithmLayerOne(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_), data(data_)
{
    border_field_temp = 0;
    neighbor_field_temp = 0;
    num_of_neighbors_temp = 0;
    field_value_temp = 0;
    border = nullptr;
}

AlgorithmLayerOne::~AlgorithmLayerOne() {}

bool AlgorithmLayerOne::Run()
{
    const unsigned int number_of_clicks_before = grid.left_click_counter + grid.right_click_counter;
    const unsigned int border_index_max = data.border_index;
    unsigned char flags_count = 0;
    unsigned char not_visible_count = 0;
    unsigned int i = 0;
    unsigned int j = 0;

    border = data.border;

    for(i = 0; i < border_index_max; i++)
    {
        border_field_temp = border[i];
        flags_count = 0;
        not_visible_count = 0;
        num_of_neighbors_temp = grid.neighbors[border_field_temp].Len();
        for(j = 0; j < num_of_neighbors_temp; j++)
        {
            neighbor_field_temp = grid.neighbors[border_field_temp][j];
            if(grid.is_flag[neighbor_field_temp]) flags_count++;
            else if(!grid.is_visible[neighbor_field_temp]) not_visible_count++;
        }
        field_value_temp = grid.FieldValue(border_field_temp);
        if(field_value_temp == flags_count)
        {
            for(j = 0; j < num_of_neighbors_temp; j++)
            {
                neighbor_field_temp = grid.neighbors[border_field_temp][j];
                if(!grid.is_flag[neighbor_field_temp] && !grid.is_visible[neighbor_field_temp])
                    grid.LeftClick(neighbor_field_temp);
            }
        }
        else if(field_value_temp == flags_count + not_visible_count)
        {
            for(j = 0; j < num_of_neighbors_temp; j++)
            {
                neighbor_field_temp = grid.neighbors[border_field_temp][j];
                if(!grid.is_flag[neighbor_field_temp] && !grid.is_visible[neighbor_field_temp])
                    grid.RightClick(neighbor_field_temp);
            }
        }
    }
    const unsigned int number_of_clicks_after = grid.left_click_counter + grid.right_click_counter;
    return number_of_clicks_after > number_of_clicks_before;
}
