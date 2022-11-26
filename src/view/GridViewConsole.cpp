#include "GridViewConsole.hpp"

using namespace std;

GridViewConsole::GridViewConsole(Grid& grid) : GridView(grid)
{
    row_indicator_max_w = to_string(grid.H).length();
    is_wider_than_10 = (grid.W > 10);
}

GridViewConsole::~GridViewConsole() {}

void GridViewConsole::Display()
{
    stringstream output;
	// ofstream output;
	// output.open("E:\\Projects\\R_Solver\\build\\temp.txt");

	output << endl;
    if(is_wider_than_10)
    {
        output << setw(row_indicator_max_w + 1) << "";
		for(size_t i = 0; i < grid.W; i+=10) output << setw(10) << left << i;
		output << endl;
    }

	output << setw(row_indicator_max_w + 1) << "";
	for(size_t i = 0; i < grid.W; i++) output << i % 10;
	output << endl;

	output << setw(row_indicator_max_w) << "" << "+" << setfill('-') << setw(grid.W) << "" << "+" << setfill(' ') << endl;

    for(size_t i = 0; i < grid.H; i++)
	{
		output << setw(row_indicator_max_w) << right << i << "|";
		for(size_t j = 0; j < grid.W; j++)
		{
			uint32_t f = i * grid.W + j;
            if(grid.is_flag[f]) output << "x";
			else if(!grid.is_visible[f]) output << "#";
			else if(grid.is_mine[f]) output << "*";
			else if(grid.FieldValue(f) == 0) output << " ";
			else output << to_string(grid.FieldValue(f));
		}
		output << "|" << left << i << endl;
	}

	output << setw(row_indicator_max_w) << "" << "+" << setfill('-') << setw(grid.W) << "" << "+" << setfill(' ') << endl;

	output << setw(row_indicator_max_w + 1) << "";
	for(size_t i = 0; i < grid.W; i++) output << i % 10;
	output << endl;

    if(is_wider_than_10)
    {
        output << setw(row_indicator_max_w + 1) << "";
		for(size_t i = 0; i < grid.W; i+=10) output << setw(10) << left << i;
		output << endl;
    }
	//std::system("cls");  // this is very ugly
    cout << output.str();
	//output.close();
}
