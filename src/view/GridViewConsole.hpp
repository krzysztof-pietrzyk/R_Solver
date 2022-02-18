#ifndef GridViewConsole_hpp
#define GridViewConsole_hpp

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

    void Display();

    private:

    unsigned int row_indicator_max_w;

    bool is_wider_than_10;
};

#endif
