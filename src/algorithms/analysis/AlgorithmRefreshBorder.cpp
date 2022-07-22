#include "AlgorithmRefreshBorder.hpp"

AlgorithmRefreshBorder::AlgorithmRefreshBorder(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_, data_) {}

AlgorithmRefreshBorder::~AlgorithmRefreshBorder() {}

AlgorithmStatus AlgorithmRefreshBorder::Run()
{
    if(data.last_read_index_border == grid.visible_fields_index &&
        data.last_read_index_border_flags == grid.flags_index) return AlgorithmStatus::NO_STATUS;
    
    const unsigned int border_index_old = data.border_index;
    const unsigned int visible_fields_new_index = grid.visible_fields_index;
    bool at_least_one_not_visible = false;
    unsigned int border_index_new = 0;
    size_t i, j = 0;

    const std::vector<unsigned int>& border_old = data.border_internal_indicator ? data.border_internal_0 : data.border_internal_1;
    std::vector<unsigned int>& border_new = data.border_internal_indicator ? data.border_internal_1 : data.border_internal_0;
    for(i = 0; i < border_index_old; i++)
    {
        const unsigned int border_field_temp = border_old[i];
        at_least_one_not_visible = false;
        for(const unsigned int& neighbor_field : grid.neighbors[border_field_temp])
        {
            if(!grid.is_visible[neighbor_field] && !grid.is_flag[neighbor_field])
            {
                at_least_one_not_visible = true;
                break;
            }
        }
        if(at_least_one_not_visible) border_new[border_index_new++] = border_field_temp;
        else data.is_border[border_field_temp] = false;
    }

    for(i = data.last_read_index_border; i < visible_fields_new_index; i++)
    {
        const unsigned int visible_field_temp = grid.visible_fields[i];
        at_least_one_not_visible = false;
        for(const unsigned int& neighbor_field : grid.neighbors[visible_field_temp])
        {
            if(!grid.is_visible[neighbor_field] && !grid.is_flag[neighbor_field])
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
    data.last_read_index_border_flags = grid.flags_index;
    data.border_internal_indicator = !data.border_internal_indicator;
    data.border_index = border_index_new;
    return AlgorithmStatus::NO_STATUS;
}