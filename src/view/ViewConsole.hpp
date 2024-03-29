#ifndef VIEW_CONSOLE_HPP
#define VIEW_CONSOLE_HPP

// project includes
#include "ViewIf.hpp"
#include "../grid/GridDimensions.hpp"

// std includes
#include <map>
#include <sstream>
#include <vector>

// forward declarations
class GridViewIf;
enum class FieldType;


class ViewConsole : public ViewIf
{
    public:

    ViewConsole(GridViewIf& grid_);

    ~ViewConsole();

    virtual void Display() override;

    protected:

    GridViewIf& grid;

    const GridDimensions grid_dim;
    const uint32_t row_indicator_max_w;
    const bool is_wider_than_10;

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
