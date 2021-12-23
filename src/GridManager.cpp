#include "GridManager.hpp"

GridManager::GridManager()
{
    left_click_counter = 0;
    right_click_counter = 0;
    is_lost = false;
}

GridManager::~GridManager() {}

unsigned char GridManager::FieldValue(unsigned int field)
{
    if(!is_visible[field]) throw std::invalid_argument("ERROR: Attempting to read a value of a covered field!");
    else return field_values[field];
}

//protected
void GridManager::Clear()
{
    left_click_counter = 0;
    right_click_counter = 0;
    is_lost = false;
}
