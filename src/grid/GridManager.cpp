#include "GridManager.hpp"

GridManager::GridManager(uint16_t w, uint16_t h, uint32_t m)
    : W(w), H(h), M(m), S(w * h), NM(S - M)
{
    visible_fields = std::vector<uint32_t>(S, 0);
    visible_fields_index = 0;
	is_visible = std::vector<bool>(S, false);
    
    flags = std::vector<uint32_t>(S, 0);
    flags_index = 0;
    is_flag = std::vector<bool>(S, false);

    neighbors = std::vector<std::vector<uint32_t>>(S, std::vector<uint32_t>());

    field_values = std::vector<uint8_t>(S, 0);

    left_click_counter = 0;
    right_click_counter = 0;
    is_lost = false;
}

GridManager::~GridManager() {}

uint8_t GridManager::FieldValue(uint32_t field)
{
    if(!CheckVisible(field))
    {
        throw std::invalid_argument("ERROR: GridManager: Attempting to read a value of a covered field!");
    }
    return field_values[field];
}

//protected
void GridManager::Clear()
{
    is_visible.assign(S, false);
    // Zero the index - old data remains in the array, but will be overwritten before it is used
    visible_fields_index = 0;
    is_flag.assign(S, false);
    // Zero the index - old data remains in the array, but will be overwritten before it is used
    flags_index = 0;

    left_click_counter = 0;
    right_click_counter = 0;
    is_lost = false;
}

bool GridManager::CheckVisible(uint32_t field)
{
    return is_visible[field];
}
