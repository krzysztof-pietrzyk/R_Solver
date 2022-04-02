#include "AlgorithmRefreshSections.hpp"

#include <iostream>
using namespace std;

AlgorithmRefreshSections::AlgorithmRefreshSections(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_), data(data_) {}

AlgorithmRefreshSections::~AlgorithmRefreshSections() {}

bool AlgorithmRefreshSections::Run()
{
    const unsigned int border_l = data.border_index;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    size_t l = 0;
    unsigned char current_section_neighbors_index = 0;
    unsigned char current_section_length = 0;
    unsigned int current_section_offset = 0;
    unsigned int current_section_neighbors_offset = 0;
    unsigned int current_border_field = 0;
    unsigned int neighbor_section_temp = 0;
    unsigned int section_value_temp = 0;
    unsigned int neighbor_field = 0;
    unsigned int neighbor_of_neighbor = 0;
    bool duplicate_temp = false;
    const std::vector<unsigned int>& border = data.GetBorder();
    data.sections_origins_index = 0;

    // iterate through border fields
    for(i = 0; i < border_l; i++)
    {
        current_section_length = 0;
        current_border_field = border[i];
        current_section_offset = current_border_field * MAX_SECTION_LENGTH;
        current_section_neighbors_offset = current_border_field * MAX_SECTION_NEIGHBORS;
        section_value_temp = grid.FieldValue(current_border_field);
        current_section_neighbors_index = 0;

        // iterate through each border field's neigbors
        for_grid_neighbors_of(current_border_field)
        {
            neighbor_field = grid.neighbors[x];
            // count the number of flags already marked around the current_border_field
            if(grid.is_flag[neighbor_field]) { section_value_temp--; continue; }
            // if this neighbor is already visible, ignore it
            else if(grid.is_visible[neighbor_field]) { continue; }
            // add this neighbor to the section
            data.sections[current_section_offset + current_section_length++] = neighbor_field;
            // iterate through the neighbors of that neighbor, in order to determine
            // potential neighbour sections of this section
            const unsigned int first_neighbor_index = neighbor_field * GridManager::MAX_NEIGHBORS;
            const unsigned int last_neighbor_index = first_neighbor_index + grid.neighbors_l[neighbor_field];
            for(size_t x2 = first_neighbor_index; x2 < last_neighbor_index; x2++)
            {
                neighbor_of_neighbor = grid.neighbors[x2];
                // if this neighbor is not on border or is the currently considered field, ignore it
                if(!data.is_border[neighbor_of_neighbor] || neighbor_of_neighbor == current_border_field) { continue; }
                duplicate_temp = false;
                // iterate through neighbors of this section, which have already been found before
                // in order to filter duplicates
                for(l = 0; l < current_section_neighbors_index; l++)
                {
                    if(data.sections_neighbors[current_section_neighbors_offset + l] == neighbor_of_neighbor)
                    {
                        duplicate_temp = true;
                        break;
                    }
                }
                if(!duplicate_temp) 
                {
                    // only add this to section neighbors if it's not a duplicate
                    data.sections_neighbors[current_section_neighbors_offset + current_section_neighbors_index++] = neighbor_of_neighbor;
                }
            }
        }
        // after iterating through neighbors, save final section value, length
        data.sections_values[current_border_field] = section_value_temp;
        data.sections_l[current_border_field] = current_section_length;
        data.sections_neighbors_l[current_border_field] = current_section_neighbors_index;
        data.sections_origins[data.sections_origins_index++] = current_border_field;
        data.is_section_origin[current_border_field] = true;
    }

    // cout << "border: ";
    // for(int i = 0; i < data.border_index; i++) cout << data.GetBorder()[i] << " ";
    // cout << endl;
    // cout << "sections: ";
    // for(int i = 0; i < data.sections_origins_index; i++) cout << data.sections_origins[i] << " ";
    // cout << endl;

    return true;
}