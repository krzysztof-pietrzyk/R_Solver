#include "AlgorithmLayerOne.hpp"

AlgorithmLayerOne::AlgorithmLayerOne(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_), data(data_) {}

AlgorithmLayerOne::~AlgorithmLayerOne() {}

bool AlgorithmLayerOne::Run()
{
    const unsigned int number_of_clicks_before = grid.left_click_counter + grid.right_click_counter;
    const unsigned int border_index_max = data.border_index;
    unsigned int border_field_temp = 0;
    const unsigned int* border_temp = data.border;
    const unsigned char* neighbors_l = grid.neighbors_l;
    const bool* is_flag = grid.is_flag;
    unsigned int** neighbors = grid.neighbors;
    unsigned int* neighbors_temp;
    const bool* is_visible = grid.is_visible;
    unsigned char num_of_neighbors = 0;
    unsigned int neighbor_field_temp = 0;
    unsigned char flags_count = 0;
    unsigned char not_visible_count = 0;
    unsigned char field_value_temp = 0;
    for(int i = 0; i < border_index_max; i++)
    {
        border_field_temp = border_temp[i];
        num_of_neighbors = neighbors_l[border_field_temp];
        neighbors_temp = neighbors[border_field_temp];
        flags_count = 0;
        not_visible_count = 0;
        for(int j = 0; j < num_of_neighbors; j++)
        {
            neighbor_field_temp = neighbors_temp[j];
            if(is_flag[neighbor_field_temp]) flags_count++;
            else if(!is_visible[neighbor_field_temp]) not_visible_count++;
        }
        field_value_temp = grid.field_values[border_field_temp];
        if(field_value_temp == flags_count)
        {
            for(int j = 0; j < num_of_neighbors; j++)
            {
                neighbor_field_temp = neighbors_temp[j];
                if(!is_flag[neighbor_field_temp] && !is_visible[neighbor_field_temp]) grid.LeftClick(neighbor_field_temp);
            }
        }
        else if(field_value_temp == flags_count + not_visible_count)
        {
            for(int j = 0; j < num_of_neighbors; j++)
            {
                neighbor_field_temp = neighbors_temp[j];
                if(!is_flag[neighbor_field_temp] && !is_visible[neighbor_field_temp]) grid.RightClick(neighbor_field_temp);
            }
        }
    }
    const unsigned int number_of_clicks_after = grid.left_click_counter + grid.right_click_counter;
    return number_of_clicks_after > number_of_clicks_before;
}
