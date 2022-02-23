#include "GridManager.hpp"

GridManager::GridManager(unsigned short int w, unsigned short int h, unsigned int m) :
    W(w), H(h), M(m), S(w * h),
    visible_fields(Buffer(S)), is_visible(BitMask(S)),
    flags(Buffer(S)), is_flag(BitMask(S)),
    field_values(ValueTable(S)), neighbors(Buffer2D(S, 8))
{
    left_click_counter = 0;
    right_click_counter = 0;
    is_lost = false;
}

GridManager::~GridManager() {}

unsigned char GridManager::FieldValue(unsigned int field)
{
    if(!is_visible[field]) 
    {
        throw std::invalid_argument("ERROR: Attempting to read a value of a covered field! " + (unsigned int)(field));
    }
    else return field_values[field];
}

//protected
void GridManager::Clear()
{
    left_click_counter = 0;
    right_click_counter = 0;
    is_lost = false;

    is_visible.Clear();
    visible_fields.Clear();
    is_flag.Clear();
    flags.Clear();
    field_values.Clear();
}
