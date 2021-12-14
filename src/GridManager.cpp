#include "GridManager.hpp"

#include <iostream>
using namespace std;

GridManager::GridManager(unsigned short int w, unsigned short int h, unsigned int m) : Grid(w, h, m) 
{
    left_click_counter = 0;
    right_click_counter = 0;
    generator = GridGeneratorFactory::Create(GridGeneratorType::GENERATOR_UNSAFE, *this);
    view = GridViewFactory::Create(GridViewType::GRID_VIEW_CONSOLE, *this);
    is_lost = false;

    is_face = new bool[S] {false};
    face_internal_0 = new unsigned int[S] {0};
    face_internal_1 = new unsigned int[S] {0};
    face = face_internal_0;
    face_internal_indicator = false;
    face_index = 0;
    last_read_index_face = 0;

    is_border = new bool[S] {0};
    border_internal_0 = new unsigned int[S] {0};
    border_internal_1 = new unsigned int[S] {0};
    border = border_internal_0;
    border_internal_indicator = false;
    border_index = 0;
    last_read_index_border = 0;
}

GridManager::~GridManager() 
{
    delete[] is_face;
    delete[] face_internal_0;
    delete[] face_internal_1;
    delete[] is_border;
    delete[] border_internal_0;
    delete[] border_internal_1;

    delete generator;
    delete view;
}

void GridManager::Generate()
{
    Clear();
    generator->Generate();
}

void GridManager::Display()
{
    view->Display();
}

void GridManager::RefreshFace()
{
    if(last_read_index_face == visible_fields_index) return;

    const unsigned int face_index_old = face_index;
    const unsigned int visible_fields_new_index = visible_fields_index;
    unsigned int face_index_new = 0;
    unsigned int face_field_temp = 0;
    unsigned int visible_field_temp = 0;
    unsigned char num_of_neighbors = 0;
    unsigned int neighbor_field_temp = 0;
    unsigned int* neighbors_temp;
    unsigned int* face_old = face_internal_indicator ? face_internal_0 : face_internal_1;
    unsigned int* face_new = face_internal_indicator ? face_internal_1 : face_internal_0;
    
    for(int i = 0; i < face_index_old; i++)
    {
        face_field_temp = face_old[i];
        if(!is_visible[face_field_temp] && !is_flag[face_field_temp]) face_new[face_index_new++] = face_field_temp;
        else is_face[face_field_temp] = false;
    }

    for(int i = last_read_index_face; i < visible_fields_new_index; i++)
    {
        visible_field_temp = visible_fields[i];
        num_of_neighbors = neighbors_l[visible_field_temp];
        neighbors_temp = neighbors[visible_field_temp];
        for(int j = 0; j < num_of_neighbors; j++)
        {
            neighbor_field_temp = neighbors_temp[j];
            if(!is_visible[neighbor_field_temp] && !is_flag[neighbor_field_temp] && !is_face[neighbor_field_temp])
            {
                is_face[neighbor_field_temp] = true;
                face_new[face_index_new++] = neighbor_field_temp;
            }
        }
    }

    last_read_index_face = visible_fields_new_index;
    face = face_new;
    face_internal_indicator = !face_internal_indicator;
    face_index = face_index_new;
}

void GridManager::RefreshBorder()
{
    if(last_read_index_border == visible_fields_index) return;
    const unsigned int border_index_old = border_index;
    const unsigned int visible_fields_new_index = visible_fields_index;
    unsigned int border_index_new = 0;
    unsigned int border_field_temp = 0;
    unsigned int visible_field_temp = 0;
    unsigned char num_of_neighbors = 0;
    unsigned int neighbor_field_temp = 0;
    unsigned int* neighbors_temp;
    bool at_least_one_not_visible = false;

    unsigned int* border_old = border_internal_indicator ? border_internal_0 : border_internal_1;
    unsigned int* border_new = border_internal_indicator ? border_internal_1 : border_internal_0;

    for(int i = 0; i < border_index_old; i++)
    {
        border_field_temp = border_old[i];
        num_of_neighbors = neighbors_l[border_field_temp];
        neighbors_temp = neighbors[border_field_temp];
        at_least_one_not_visible = false;
        for(int j = 0; j < num_of_neighbors; j++)
        {
            neighbor_field_temp = neighbors_temp[j];
            if(!is_visible[neighbor_field_temp] && !is_flag[neighbor_field_temp])
            {
                at_least_one_not_visible = true;
                break;
            }
        }
        if(at_least_one_not_visible) border_new[border_index_new++] = border_field_temp;
        else is_border[border_field_temp] = false;
    }

    for(int i = last_read_index_border; i < visible_fields_new_index; i++)
    {
        visible_field_temp = visible_fields[i];
        num_of_neighbors = neighbors_l[visible_field_temp];
        neighbors_temp = neighbors[visible_field_temp];
        at_least_one_not_visible = false;
        for(int j = 0; j < num_of_neighbors; j++)
        {
            neighbor_field_temp = neighbors_temp[j];
            if(!is_visible[neighbor_field_temp] && !is_flag[neighbor_field_temp])
            {
                at_least_one_not_visible = true;
                break;
            }
        }
        if(at_least_one_not_visible)
        {
            is_border[visible_field_temp] = true;
            border_new[border_index_new++] = visible_field_temp;
        }
    }

    last_read_index_border = visible_fields_new_index;
    border = border_new;
    border_internal_indicator = !border_internal_indicator;
    border_index = border_index_new;
}

void GridManager::LeftClick(unsigned int field)
{
    //cout << "Left Click @ " << field << endl;
    if(is_lost) return;
    left_click_counter++;
    is_visible[field] = true;
    visible_fields[visible_fields_index++] = field;
    if(is_mine[field]) is_lost = true;
    else if(field_values[field] == 0) ZeroChainReaction(field); 
}

void GridManager::RightClick(unsigned int field)
{
    //cout << "Right Click @ " << field << endl;
    if(is_lost) return;
    right_click_counter++;
    is_flag[field] = true;
    flags[flags_index++] = field;
}

//private
void GridManager::Clear()
{
    for(int i = 0; i < face_index; i++) is_face[face[i]] = false;
    for(int i = 0; i < border_index; i++) is_border[border[i]] = false;
    face_index = 0;
    border_index = 0;
    last_read_index_face = 0;
    last_read_index_border = 0;
    is_lost = false;
}
