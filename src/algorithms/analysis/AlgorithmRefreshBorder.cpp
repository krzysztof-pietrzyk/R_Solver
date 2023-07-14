#include "AlgorithmRefreshBorder.hpp"

AlgorithmRefreshBorder::AlgorithmRefreshBorder(GridAccessPlayerIf& grid_, AlgorithmDataStorage& data_)
    : Algorithm(grid_, data_),
    D_border_index(GetModifiableAlgorithmDataStorageReference().border_index),
    D_border_last_visible_fields_index(GetModifiableAlgorithmDataStorageReference().border_last_visible_fields_index),
    D_border(GetModifiableAlgorithmDataStorageReference().border),
    D_is_border(GetModifiableAlgorithmDataStorageReference().is_border)
{}

AlgorithmRefreshBorder::~AlgorithmRefreshBorder() {}

AlgorithmStatus AlgorithmRefreshBorder::Execution()
{  
    const uint32_t visible_fields_old_index = data.border_last_visible_fields_index;
    const uint32_t visible_fields_new_index = visible.CurrentIndex();

    if(visible_fields_new_index == visible_fields_old_index) return AlgorithmStatus::NO_STATUS;

    uint32_t border_index_new = 0;

    FilterOldBorderContent(border_index_new);
    AddNewContentToBorder(border_index_new);

    D_border_index = border_index_new;
    D_border_last_visible_fields_index = visible_fields_new_index;

    return AlgorithmStatus::NO_STATUS;
}

void AlgorithmRefreshBorder::FilterOldBorderContent(uint32_t& border_index_new) const
{
    const uint32_t border_index_old = data.border_index;
    for(size_t i = 0; i < border_index_old; i++)
    {
        const uint32_t border_field = data.border[i];
        if(HasAtLeastOneNotVisibleNeighbor(border_field))
        {
            D_border[border_index_new++] = border_field;
        }
        else 
        {
            D_is_border[border_field] = false;
        }
    }
}

void AlgorithmRefreshBorder::AddNewContentToBorder(uint32_t& border_index_new) const
{
    const uint32_t visible_fields_old_index = data.border_last_visible_fields_index;
    const uint32_t visible_fields_new_index = visible.CurrentIndex();
    for(size_t i = visible_fields_old_index; i < visible_fields_new_index; i++)
    {
        const uint32_t visible_field = visible[i];
        if(HasAtLeastOneNotVisibleNeighbor(visible_field))
        {
            D_is_border[visible_field] = true;
            D_border[border_index_new++] = visible_field;
        }
    }
}

bool AlgorithmRefreshBorder::HasAtLeastOneNotVisibleNeighbor(uint32_t field) const
{
    bool at_least_one_not_visible = false;
    const std::vector<uint32_t>& field_neighbors = grid.GetFieldNeighbors(field);
    for(const uint32_t& neighbor_field : field_neighbors)
    {
        if(!visible.Contains(neighbor_field) && !flagged.Contains(neighbor_field))
        {
            at_least_one_not_visible = true;
            break;
        }
    }
    return at_least_one_not_visible;
}
