#include "GridManager.hpp"

GridManager::GridManager(unsigned short int w, unsigned short int h, unsigned int m)
{
    W = w;
    H = h;
    M = m;
    S = w * h;

    // Mines should be less than Size, at least 1 mine, and Size can't be arbitrarily large
    // It is possible to create a 5000x5000 grid, but it's not recommended to go that big
    if(M >= S || M < 1 || S > (unsigned int)(1e+8)) throw std::invalid_argument("ERROR: Grid constructor parameters are invalid.");

    visible_fields = new unsigned int[S] {0};
    visible_fields_index = 0;
	is_visible = new bool[S] {false};

    flags = new unsigned int[S] {0};
    flags_index = 0;
    is_flag = new bool[S] {false};

    field_values = new unsigned char[S] {0};

    neighbors = new unsigned int*[S];
    neighbors_l = new unsigned char[S] {0};

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

    // Only clear the data, which may influence the next generated grid
    for(int i = 0; i < visible_fields_index; i++) is_visible[visible_fields[i]] = false;
    // Zero the index - old data remains in the array, but will be overwritten before it is used
    visible_fields_index = 0;
    for(int i = 0; i < flags_index; i++) is_flag[flags[i]] = false;
    // Zero the index - old data remains in the array, but will be overwritten before it is used
    flags_index = 0;
}
