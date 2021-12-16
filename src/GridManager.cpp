#include "GridManager.hpp"

GridManager::GridManager(unsigned short int w, unsigned short int h, unsigned int m) : Grid(w, h, m) 
{
    left_click_counter = 0;
    right_click_counter = 0;
    generator = GridGeneratorFactory::Create(GridGeneratorType::GENERATOR_UNSAFE, *this);
    view = GridViewFactory::Create(GridViewType::GRID_VIEW_CONSOLE, *this);
    is_lost = false;
}

GridManager::~GridManager() 
{
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
    is_lost = false;
}
