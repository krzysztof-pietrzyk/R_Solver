#include "GridManager.hpp"

GridManager::GridManager(unsigned short int w, unsigned short int h, unsigned int m)
    : W(w), H(h), M(m), S(w * h)
{
    visible_fields = new unsigned int[S] {0};
    visible_fields_index = 0;
	is_visible = new bool[S] {false};
    
    flags = new unsigned int[S] {0};
    flags_index = 0;
    is_flag = new bool[S] {false};

    neighbors = new unsigned int*[S];
    neighbors_l = new unsigned char[S] {0};

    field_values = new unsigned char[S] {0};

    left_click_counter = 0;
    right_click_counter = 0;
    is_lost = false;
}

GridManager::~GridManager()
{
    delete[] field_values;
    delete[] visible_fields;
    delete[] is_visible;
    delete[] flags;
    delete[] is_flag;
    for(int i = 0; i < S; i++) delete[] neighbors[i];
    delete[] neighbors;
    delete[] neighbors_l;
}

unsigned char GridManager::FieldValue(unsigned int field)
{
    if(!is_visible[field]) 
    {
        throw std::invalid_argument("ERROR: Attempting to read a value of a covered field! " + field);
    }
    else return field_values[field];
}

//protected
void GridManager::Clear()
{
    left_click_counter = 0;
    right_click_counter = 0;
    is_lost = false;
}
