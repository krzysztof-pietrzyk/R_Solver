#include "GridManager.hpp"

GridManager::GridManager(unsigned short int w, unsigned short int h, unsigned int m)
    : W(w), H(h), M(m), S(w * h), NM(S - M)
{
    visible_fields = std::vector<unsigned int>(S, 0);
    visible_fields_index = 0;
	is_visible = std::vector<bool>(S, false);
    
    flags = std::vector<unsigned int>(S, 0);
    flags_index = 0;
    is_flag = std::vector<bool>(S, false);

    neighbors = std::vector<std::vector<unsigned int>>(S, std::vector<unsigned int>());

    field_values = std::vector<unsigned char>(S, 0);

    left_click_counter = 0;
    right_click_counter = 0;
    is_lost = false;
}

GridManager::~GridManager() {}

unsigned char GridManager::FieldValue(unsigned int field)
{
    if(!is_visible[field]) 
    {
        throw std::invalid_argument("ERROR: GridManager: Attempting to read a value of a covered field! " + field);
    }
    else return field_values[field];
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
