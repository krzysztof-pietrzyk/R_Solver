// implemented header
#include "ViewConsole.hpp"

// project includes
#include "../grid/GridHash.hpp"
#include "../grid/GridViewIf.hpp"
#include "../utils/Logger.hpp"

// std includes
#include <iomanip>
#include <iostream>


const std::map<FieldType, char> ViewConsole::fields_map = 
{
    {FieldType::F_COVERED, '#'},
    {FieldType::F_FLAGGED, '.'},
    {FieldType::F_FLAGGED_INCORRECTLY, 'X'},
    {FieldType::F_MINE_EXPLODED, '*'},
    {FieldType::F_MINE_UNFLAGGED, 'o'},
    {FieldType::F_0, ' '},
    {FieldType::F_1, '1'},
    {FieldType::F_2, '2'},
    {FieldType::F_3, '3'},
    {FieldType::F_4, '4'},
    {FieldType::F_5, '5'},
    {FieldType::F_6, '6'},
    {FieldType::F_7, '7'},
    {FieldType::F_8, '8'}
};

const char ViewConsole::frame_horizontal = '-';
const char ViewConsole::frame_vertical = '|';
const char ViewConsole::frame_corner = '+';
const uint32_t ViewConsole::num_of_digits = 10U;

using std::to_string, std::endl, std::cout, std::setw, std::left, std::right, std::setfill;

ViewConsole::ViewConsole(GridViewIf& grid_)
    : grid(grid_),
    grid_dim(grid_.GetDimensions()),
    row_indicator_max_w(to_string(grid_dim.height).length()),
    is_wider_than_10(grid_dim.width > 10)
{
    LOGGER(LogLevel::INIT) << "ViewConsole";
}

ViewConsole::~ViewConsole()
{

}

void ViewConsole::Display()
{
    LOGGER(LogLevel::DEBUG) << "ViewConsole::Display";
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
		for(size_t i = 0; i < grid_dim.width; i += num_of_digits)
        {
            output << setw(num_of_digits) << left << i;
        }
		output << endl;
    }
}

void ViewConsole::DrawSmallNumberRow(std::stringstream& output)
{
	output << setw(row_indicator_max_w + 1) << "";
	for(size_t i = 0; i < grid_dim.width; i++)
    {
        output << i % num_of_digits;
    }
	output << endl;
}

void ViewConsole::DrawHorizontalBar(std::stringstream& output)
{
    output << setw(row_indicator_max_w) << "" << frame_corner << setfill(frame_horizontal) 
        << setw(grid_dim.width) << "" << frame_corner << setfill(' ') << endl;
}

void ViewConsole::DrawGridRows(std::stringstream& output, const std::vector<FieldType>& fields_to_display)
{
    for(size_t i = 0; i < grid_dim.height; i++)
	{
		output << setw(row_indicator_max_w) << right << i << frame_vertical;
		for(size_t j = 0; j < grid_dim.width; j++)
		{
			uint32_t position = i * grid_dim.width + j;
            output << fields_map.at(fields_to_display[position]);
		}
		output << frame_vertical << left << i << endl;
	}
}
