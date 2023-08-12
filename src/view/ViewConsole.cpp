#include "ViewConsole.hpp"

const std::map<FieldType, char> ViewConsole::fields_map = 
{
    {F_COVERED, '#'},
    {F_FLAGGED, '.'},
    {F_FLAGGED_INCORRECTLY, 'X'},
    {F_MINE_EXPLODED, '*'},
    {F_MINE_UNFLAGGED, 'o'},
    {F_0, ' '},
    {F_1, '1'},
    {F_2, '2'},
    {F_3, '3'},
    {F_4, '4'},
    {F_5, '5'},
    {F_6, '6'},
    {F_7, '7'},
    {F_8, '8'}
};

const char ViewConsole::frame_horizontal = '-';
const char ViewConsole::frame_vertical = '|';
const char ViewConsole::frame_corner = '+';
const uint32_t ViewConsole::num_of_digits = 10U;

using std::to_string, std::endl, std::cout, std::setw, std::left, std::right, std::setfill;

ViewConsole::ViewConsole(GridAccessViewIf& _grid)
    : grid(_grid),
    row_indicator_max_w(to_string(grid.GetHeight()).length()),
    is_wider_than_10(grid.GetWidth() > 10),
    grid_width(grid.GetWidth()),
    grid_height(grid.GetHeight())
{
    LOGGER(LOG_INIT) << "ViewConsole";
}

ViewConsole::~ViewConsole()
{

}

void ViewConsole::Display()
{
    LOGGER(LOG_DEBUG) << "ViewConsole::Display";
    const std::vector<FieldType>& fields_to_display = grid.GetFieldTypesToDisplay();

    std::stringstream output;

    DrawBigNumberRow(output);
	DrawSmallNumberRow(output);
    DrawHorizontalBar(output);
    DrawGridRows(output, fields_to_display);
	DrawHorizontalBar(output);
	DrawSmallNumberRow(output);
    DrawBigNumberRow(output);

    output << "hash: " << grid.GetHash().ToString() << endl << endl;

    cout << output.str();
}

void ViewConsole::DrawBigNumberRow(std::stringstream& output)
{
    if(is_wider_than_10)
    {
        output << setw(row_indicator_max_w + 1) << "";
		for(size_t i = 0; i < grid_width; i += num_of_digits)
        {
            output << setw(num_of_digits) << left << i;
        }
		output << endl;
    }
}

void ViewConsole::DrawSmallNumberRow(std::stringstream& output)
{
	output << setw(row_indicator_max_w + 1) << "";
	for(size_t i = 0; i < grid_width; i++)
    {
        output << i % num_of_digits;
    }
	output << endl;
}

void ViewConsole::DrawHorizontalBar(std::stringstream& output)
{
    output << setw(row_indicator_max_w) << "" << frame_corner << setfill(frame_horizontal) 
        << setw(grid_width) << "" << frame_corner << setfill(' ') << endl;
}

void ViewConsole::DrawGridRows(std::stringstream& output, const std::vector<FieldType>& fields_to_display)
{
    for(size_t i = 0; i < grid_height; i++)
	{
		output << setw(row_indicator_max_w) << right << i << frame_vertical;
		for(size_t j = 0; j < grid_width; j++)
		{
			uint32_t position = i * grid_width + j;
            output << fields_map.at(fields_to_display[position]);
		}
		output << frame_vertical << left << i << endl;
	}
}

