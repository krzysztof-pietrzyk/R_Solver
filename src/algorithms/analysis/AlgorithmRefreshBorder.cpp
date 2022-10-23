#include "AlgorithmRefreshBorder.hpp"

AlgorithmRefreshBorder::AlgorithmRefreshBorder(GridManager& grid_, AlgorithmDataStorage& data_)
    : Algorithm(grid_, data_),
    D_border_index(GetModifiableAlgorithmDataStorageReference().border_index),
    D_border_last_visible_fields_index(GetModifiableAlgorithmDataStorageReference().border_last_visible_fields_index),
    D_border(GetModifiableAlgorithmDataStorageReference().border),
    D_is_border(GetModifiableAlgorithmDataStorageReference().is_border)
{}

AlgorithmRefreshBorder::~AlgorithmRefreshBorder() {}

AlgorithmStatus AlgorithmRefreshBorder::Run()
{  
    const unsigned int visible_fields_old_index = data.border_last_visible_fields_index;
    const unsigned int visible_fields_new_index = grid.visible_fields_index;

    if(visible_fields_new_index == visible_fields_old_index) return AlgorithmStatus::NO_STATUS;

    unsigned int border_index_new = 0;

    FilterOldBorderContent(border_index_new);
    AddNewContentToBorder(border_index_new);

    D_border_index = border_index_new;
    D_border_last_visible_fields_index = visible_fields_new_index;

    return AlgorithmStatus::NO_STATUS;
}

void AlgorithmRefreshBorder::FilterOldBorderContent(unsigned int& border_index_new) const
{
    const unsigned int border_index_old = data.border_index;
    for(size_t i = 0; i < border_index_old; i++)
    {
        const unsigned int border_field = data.border[i];
        bool at_least_one_not_visible = false;
        const std::vector<unsigned int>& border_field_neighbors = grid.neighbors[border_field];
        for(const unsigned int& neighbor_field : border_field_neighbors)
        {
            if(!grid.is_visible[neighbor_field] && !grid.is_flag[neighbor_field])
            {
                at_least_one_not_visible = true;
                break;
            }
        }
        if(at_least_one_not_visible) D_border[border_index_new++] = border_field;
        else D_is_border[border_field] = false;
    }
}

void AlgorithmRefreshBorder::AddNewContentToBorder(unsigned int& border_index_new) const
{
    const unsigned int visible_fields_old_index = data.border_last_visible_fields_index;
    const unsigned int visible_fields_new_index = grid.visible_fields_index;
    for(size_t i = visible_fields_old_index; i < visible_fields_new_index; i++)
    {
        const unsigned int visible_field = grid.visible_fields[i];
        bool at_least_one_not_visible = false;
        const std::vector<unsigned int>& visible_field_neighbors = grid.neighbors[visible_field];
        for(const unsigned int& neighbor_field : visible_field_neighbors)
        {
            if(!grid.is_visible[neighbor_field] && !grid.is_flag[neighbor_field])
            {
                at_least_one_not_visible = true;
                break;
            }
        }
        if(at_least_one_not_visible)
        {
            D_is_border[visible_field] = true;
            D_border[border_index_new++] = visible_field;
        }
    }
}
