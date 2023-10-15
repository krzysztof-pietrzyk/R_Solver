#include "AlgorithmBorder.hpp"

AlgorithmBorder::AlgorithmBorder(GridAccessPlayerIf& grid_, AlgorithmDataTransfer& data_)
    : Algorithm(grid_, data_),
    D_border_index(GetModifiableAlgorithmDataTransferReference().border_index),
    D_border_last_visible_fields_index(GetModifiableAlgorithmDataTransferReference().border_last_visible_fields_index),
    D_border(GetModifiableAlgorithmDataTransferReference().border),
    D_is_border(GetModifiableAlgorithmDataTransferReference().is_border)
{
    LOGGER(LogLevel::INIT) << "AlgorithmBorder";
}

AlgorithmBorder::~AlgorithmBorder() {}

AlgorithmStatus AlgorithmBorder::Execution()
{  
    const uint32_t visible_fields_old_index = data.border_last_visible_fields_index;
    const uint32_t visible_fields_new_index = visible.Index();

    if(visible_fields_new_index == visible_fields_old_index)
    {
        return AlgorithmStatus::NO_STATUS;
    }

    uint32_t border_index_new = 0;

    FilterOldBorderContent(border_index_new);
    AddNewContentToBorder(border_index_new);

    D_border_index = border_index_new;
    D_border_last_visible_fields_index = visible_fields_new_index;

    return AlgorithmStatus::NO_STATUS;
}

void AlgorithmBorder::FilterOldBorderContent(uint32_t& border_index_new) const
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

void AlgorithmBorder::AddNewContentToBorder(uint32_t& border_index_new) const
{
    const uint32_t visible_fields_old_index = data.border_last_visible_fields_index;
    const uint32_t visible_fields_new_index = visible.Index();
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

bool AlgorithmBorder::HasAtLeastOneNotVisibleNeighbor(uint32_t field) const
{
    bool at_least_one_not_visible = false;
    const std::vector<uint32_t>& field_neighbors = grid.GetNeighbors(field);
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
