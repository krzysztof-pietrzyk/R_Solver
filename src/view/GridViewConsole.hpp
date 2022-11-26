#ifndef GRID_VIEW_CONSOLE_HPP
#define GRID_VIEW_CONSOLE_HPP

#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "GridView.hpp"

class GridViewConsole : public GridView
{
    public:

    GridViewConsole(Grid& grid);

    ~GridViewConsole();

    void Display() override;

    private:

    uint32_t row_indicator_max_w;

    bool is_wider_than_10;
};

#endif
