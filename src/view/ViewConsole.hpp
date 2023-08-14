#ifndef VIEW_CONSOLE_HPP
#define VIEW_CONSOLE_HPP

#include "../grid/GridAccessViewIf.hpp"

#include "ViewIf.hpp"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>

class ViewConsole : public ViewIf
{
    public:

    ViewConsole(GridAccessViewIf& _grid);

    ~ViewConsole();

    virtual void Display() override;

    protected:

    GridAccessViewIf& grid;

    const uint32_t row_indicator_max_w;
    const bool is_wider_than_10;
    const uint32_t grid_width;
    const uint32_t grid_height;

    static const std::map<FieldType, char> fields_map;
    static const char frame_horizontal;
    static const char frame_vertical;
    static const char frame_corner;
    static const uint32_t num_of_digits;

    private:

    void DrawBigNumberRow(std::stringstream& output);
    void DrawSmallNumberRow(std::stringstream& output);
    void DrawHorizontalBar(std::stringstream& output);
    void DrawGridRows(std::stringstream& output, const std::vector<FieldType>& fields_to_display);
};

#endif
