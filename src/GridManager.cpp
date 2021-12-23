#include "GridManager.hpp"

GridManager::GridManager()
{
    left_click_counter = 0;
    right_click_counter = 0;
    is_lost = false;
}

GridManager::~GridManager() {}

//protected
void GridManager::Clear()
{
    left_click_counter = 0;
    right_click_counter = 0;
    is_lost = false;
}
