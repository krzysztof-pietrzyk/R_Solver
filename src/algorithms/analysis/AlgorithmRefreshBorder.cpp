#include "AlgorithmRefreshBorder.hpp"

AlgorithmRefreshBorder::AlgorithmRefreshBorder(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_, data_) {}

AlgorithmRefreshBorder::~AlgorithmRefreshBorder() {}

AlgorithmStatus AlgorithmRefreshBorder::Run()
{  
    const unsigned int visible_fields_old_index = data.border_last_visible_fields_index;
    const unsigned int visible_fields_new_index = grid.visible_fields_index;

    if(visible_fields_new_index == visible_fields_old_index) return AlgorithmStatus::NO_STATUS;

    std::vector<unsigned int>& border = data.border;
    unsigned int border_index_new = 0;

    FilterOldBorderContent(border, border_index_new);
    AddNewContentToBorder(border, border_index_new);

    data.border_index = border_index_new;
    data.border_last_visible_fields_index = visible_fields_new_index;

    return AlgorithmStatus::NO_STATUS;
}

void AlgorithmRefreshBorder::FilterOldBorderContent(std::vector<unsigned int>& border, unsigned int& border_index_new) const
{
    const unsigned int border_index_old = data.border_index;
    for(size_t i = 0; i < border_index_old; i++)
    {
        const unsigned int border_field = border.at(i);
        bool at_least_one_not_visible = false;
        const std::vector<unsigned int>& border_field_neighbors = grid.neighbors.at(border_field);
        for(const unsigned int& neighbor_field : border_field_neighbors)
        {
            if(!grid.is_visible.at(neighbor_field) && !grid.is_flag.at(neighbor_field))
            {
                at_least_one_not_visible = true;
                break;
            }
        }
        if(at_least_one_not_visible) border.at(border_index_new++) = border_field;
        else data.is_border.at(border_field) = false;
    }
}

void AlgorithmRefreshBorder::AddNewContentToBorder(std::vector<unsigned int>& border, unsigned int& border_index_new) const
{
    const unsigned int visible_fields_old_index = data.border_last_visible_fields_index;
    const unsigned int visible_fields_new_index = grid.visible_fields_index;
    for(size_t i = visible_fields_old_index; i < visible_fields_new_index; i++)
    {
        const unsigned int visible_field = grid.visible_fields.at(i);
        bool at_least_one_not_visible = false;
        const std::vector<unsigned int>& visible_field_neighbors = grid.neighbors.at(visible_field);
        for(const unsigned int& neighbor_field : visible_field_neighbors)
        {
            if(!grid.is_visible.at(neighbor_field) && !grid.is_flag.at(neighbor_field))
            {
                at_least_one_not_visible = true;
                break;
            }
        }
        if(at_least_one_not_visible)
        {
            data.is_border.at(visible_field) = true;
            border.at(border_index_new++) = visible_field;
        }
    }
}
