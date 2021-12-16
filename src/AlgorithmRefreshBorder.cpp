#include "AlgorithmRefreshBorder.hpp"

AlgorithmRefreshBorder::AlgorithmRefreshBorder(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_), data(data_) {}

AlgorithmRefreshBorder::~AlgorithmRefreshBorder() {}

bool AlgorithmRefreshBorder::Run()
{
    if(data.last_read_index_border == grid.visible_fields_index) return true;
    const unsigned int border_index_old = data.border_index;
    const unsigned int visible_fields_new_index = grid.visible_fields_index;
    unsigned int border_index_new = 0;
    unsigned int border_field_temp = 0;
    unsigned int visible_field_temp = 0;
    unsigned char num_of_neighbors = 0;
    unsigned int neighbor_field_temp = 0;
    unsigned int* neighbors_temp;
    bool at_least_one_not_visible = false;

    unsigned int* border_old = data.border_internal_indicator ? data.border_internal_0 : data.border_internal_1;
    unsigned int* border_new = data.border_internal_indicator ? data.border_internal_1 : data.border_internal_0;

    for(int i = 0; i < border_index_old; i++)
    {
        border_field_temp = border_old[i];
        num_of_neighbors = grid.neighbors_l[border_field_temp];
        neighbors_temp = grid.neighbors[border_field_temp];
        at_least_one_not_visible = false;
        for(int j = 0; j < num_of_neighbors; j++)
        {
            neighbor_field_temp = neighbors_temp[j];
            if(!grid.is_visible[neighbor_field_temp] && !grid.is_flag[neighbor_field_temp])
            {
                at_least_one_not_visible = true;
                break;
            }
        }
        if(at_least_one_not_visible) border_new[border_index_new++] = border_field_temp;
        else data.is_border[border_field_temp] = false;
    }

    for(int i = data.last_read_index_border; i < visible_fields_new_index; i++)
    {
        visible_field_temp = grid.visible_fields[i];
        num_of_neighbors = grid.neighbors_l[visible_field_temp];
        neighbors_temp = grid.neighbors[visible_field_temp];
        at_least_one_not_visible = false;
        for(int j = 0; j < num_of_neighbors; j++)
        {
            neighbor_field_temp = neighbors_temp[j];
            if(!grid.is_visible[neighbor_field_temp] && !grid.is_flag[neighbor_field_temp])
            {
                at_least_one_not_visible = true;
                break;
            }
        }
        if(at_least_one_not_visible)
        {
            data.is_border[visible_field_temp] = true;
            border_new[border_index_new++] = visible_field_temp;
        }
    }

    data.last_read_index_border = visible_fields_new_index;
    data.border = border_new;
    data.border_internal_indicator = !data.border_internal_indicator;
    data.border_index = border_index_new;
    return true;
}