#include "AlgorithmRefreshSections.hpp"

#include <iostream>
using namespace std;

AlgorithmRefreshSections::AlgorithmRefreshSections(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_), data(data_)
{
    current_border_field = 0;
    neighbor_temp = 0;
    neighbor_section_temp = 0;
    neighbors_of_neighbor_temp = nullptr;
    neighbors_of_neighbor_temp_l = 0;
    potential_section_neighbor = 0;
    section_value_temp = 0;
    border_field_neighbors = nullptr;
    border_field_neighbors_l = 0;
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
    unsigned int current_section_offset = 0;
    unsigned int current_section_neighbors_offset = 0;
    unsigned char current_section_neighbors_index = 0;
    unsigned char current_section_length = 0;
    bool duplicate_temp = false;

    // iterate through border fields
    for(i = 0; i < border_l; i++)
    {
        current_section_length = 0;
        current_border_field = data.border[i];
        border_field_neighbors = grid.neighbors[current_border_field];
        border_field_neighbors_l = grid.neighbors_l[current_border_field];
        section_value_temp = grid.FieldValue(current_border_field);
        current_section_neighbors_index = 0;
        // a section can have a max of 8 fields in it
        // the array size is the map size * 8, to allow room for all the possible sections
        // the formatting of this array is as follows:
        // elements [0-7] contain the section around 0th field
        // elements [8-15] contain the section around 1st field and so on
        // this is why the offset needs to be calculated
        current_section_offset = current_border_field * 8;
        // similar as above, except each section can have a max of 16 neighbors (theoretically)
        current_section_neighbors_offset = current_border_field * 16;

        // iterate through each border field's neigbors
        for(j = 0; j < border_field_neighbors_l; j++)
        {
            neighbor_temp = border_field_neighbors[j];
            // count the number of flags already marked around the current_border_field
            if(grid.is_flag[neighbor_temp]) { section_value_temp--; }
            // if this neighbor is already visible, ignore it
            else if(grid.is_visible[neighbor_temp]) { continue; }
            // add this neighbor to the section
            data.sections[current_section_offset + current_section_length++] = neighbor_temp;
            neighbors_of_neighbor_temp = grid.neighbors[neighbor_temp];
            neighbors_of_neighbor_temp_l = grid.neighbors_l[neighbor_temp];
            // iterate through the neighbors of that neighbor, in order to determine
            // potential neighbour sections of this section
            for(k = 0; k < neighbors_of_neighbor_temp_l; k++)
            {
                potential_section_neighbor = neighbors_of_neighbor_temp[k];
                // if this neighbor is not on border or is the currently considered field, ignore it
                if(!data.is_border[potential_section_neighbor] || potential_section_neighbor == current_border_field) { continue; }
                duplicate_temp = false;
                // iterate through neighbors of this section, which have already been found before
                // in order to filter duplicates
                for(l = 0; l < current_section_neighbors_index; l++)
                {
                    if(data.sections_neighbors[current_section_neighbors_offset + l] == potential_section_neighbor)
                    {
                        duplicate_temp = true;
                        break;
                    }
                }
                if(!duplicate_temp) 
                {
                    // only add this to section neighbors if it's not a duplicate
                    data.sections_neighbors[current_section_neighbors_offset + current_section_neighbors_index++] = potential_section_neighbor;
                }
            }
        }
        // after iterating through neighbors, save final section value, length
        data.sections_values[current_border_field] = section_value_temp;
        data.sections_l[current_border_field] = current_section_length;
        data.sections_neighbors_l[current_border_field] = current_section_neighbors_index;
        cout << "border: " << current_border_field << ", value: " << int(section_value_temp) << ", length: " << int(current_section_length);
        cout << ", neighbors: ";
        for(int j = 0; j < current_section_neighbors_index; j++)
            cout << data.sections_neighbors[current_border_field * 16 + j] << ", ";
        cout << " neighbors_length: " << int(data.sections_neighbors_l[current_border_field]) << endl;
    }

    return true;
}