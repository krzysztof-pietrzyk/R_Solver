#include "AlgorithmRefreshSections.hpp"

#include <iostream>
using namespace std;

AlgorithmRefreshSections::AlgorithmRefreshSections(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_), data(data_)
{
    current_border_field = 0;
    neighbor_temp = 0;
    neighbor_section_temp = 0;
    neighbors_of_neighbor_temp_l = 0;
    potential_section_neighbor = 0;
    section_value_temp = 0;
    border_field_neighbors_l = 0;
    section_temp = nullptr;
    section_neighbors_temp = nullptr;
}

AlgorithmRefreshSections::~AlgorithmRefreshSections()
{

}

bool AlgorithmRefreshSections::Run()
{
    const unsigned int border_l = data.border_index;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    unsigned int l = 0;
    unsigned char current_section_neighbors_index = 0;
    unsigned char current_section_length = 0;
    bool duplicate_temp = false;

    // iterate through border fields
    for(i = 0; i < border_l; i++)
    {
        current_section_length = 0;
        current_border_field = data.border[i];
        border_field_neighbors_l = grid.neighbors[current_border_field].Len();
        section_value_temp = grid.FieldValue(current_border_field);
        current_section_neighbors_index = 0;

        // iterate through each border field's neigbors
        for(j = 0; j < border_field_neighbors_l; j++)
        {
            neighbor_temp = grid.neighbors[current_border_field][j];
            // count the number of flags already marked around the current_border_field
            if(grid.is_flag[neighbor_temp]) { section_value_temp--; continue; }
            // if this neighbor is already visible, ignore it
            else if(grid.is_visible[neighbor_temp]) { continue; }
            // add this neighbor to the section
            section_temp = data.sections[current_border_field];
            section_temp[current_section_length++] = neighbor_temp;
            neighbors_of_neighbor_temp_l = grid.neighbors[neighbor_temp].Len();
            section_neighbors_temp = data.sections_neighbors[current_border_field];
            // iterate through the neighbors of that neighbor, in order to determine
            // potential neighbour sections of this section
            for(k = 0; k < neighbors_of_neighbor_temp_l; k++)
            {
                potential_section_neighbor = grid.neighbors[neighbor_temp][k];
                // if this neighbor is not on border or is the currently considered field, ignore it
                if(!data.is_border[potential_section_neighbor] || potential_section_neighbor == current_border_field) { continue; }
                duplicate_temp = false;
                // iterate through neighbors of this section, which have already been found before
                // in order to filter duplicates
                for(l = 0; l < current_section_neighbors_index; l++)
                {
                    if(section_neighbors_temp[l] == potential_section_neighbor)
                    {
                        duplicate_temp = true;
                        break;
                    }
                }
                if(!duplicate_temp) 
                {
                    // only add this to section neighbors if it's not a duplicate
                    section_neighbors_temp[current_section_neighbors_index++] = potential_section_neighbor;
                }
            }
        }
        // after iterating through neighbors, save final section value, length
        data.sections_values[current_border_field] = section_value_temp;
        data.sections_l[current_border_field] = current_section_length;
        data.sections_neighbors_l[current_border_field] = current_section_neighbors_index;
    }

    // for(i = 0; i < data.border_index; i++)
    // {
    //     unsigned int current_field = data.border[i];
    //     cout << "Section #" << i << ": [ ";
    //     for(j = 0; j < data.sections_l[current_field]; j++)
    //     {
    //         cout << data.sections_big[current_field * 8 + j] << " ";
    //     }
    //     cout << "], value: " << int(data.sections_values[current_field]);
    //     cout << ", origin: " << current_field;
    //     cout << ", length: " << int(data.sections_l[current_field]);
    //     cout << ", neighbors_l: " << int(data.sections_neighbors_l[current_field]);
    //     cout << ", neighbors: [ ";
    //     for(j = 0; j < data.sections_neighbors_l[current_field]; j++)
    //     {
    //         cout << data.sections_neighbors_big[current_field * 16 + j] << " ";
    //     }
    //     cout << "]" << endl;
    // }

    return true;
}