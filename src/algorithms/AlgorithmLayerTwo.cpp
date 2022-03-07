#include "AlgorithmLayerTwo.hpp"

AlgorithmLayerTwo::AlgorithmLayerTwo(GridManager& grid_, AlgorithmDataStorage& data_) : Algorithm(grid_), data(data_) {}

AlgorithmLayerTwo::~AlgorithmLayerTwo() {}

bool AlgorithmLayerTwo::Run()
{
    const unsigned int sections_l = data.border_index;

    bool success = false;

    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    unsigned int l = 0;

    unsigned int origin = 0;
    unsigned int* section_origin = nullptr;
    unsigned char section_l_origin = 0;
    unsigned char neighbors_l_origin = 0;
    unsigned int* origin_neighbors = nullptr;
    unsigned char section_value = 0;
    unsigned int* neighbor_section = nullptr;
    unsigned char neighbor_section_l = 0;
    unsigned int neighbor_section_origin = 0;
    unsigned char common_fields_l = 0;
    unsigned char origin_value = 0;
    unsigned char neighbor_value = 0;
    
    for(i = 0; i < sections_l; i++)
    {
        origin = data.border[i];
        neighbors_l_origin = data.sections_neighbors_l[origin];
        // ignore sections that have no neighbors
        if(neighbors_l_origin == 0) { continue; }
        section_l_origin = data.sections_l[origin];
        // ignore sections with less than 2 fields
        if(section_l_origin < 2) { continue; }

        section_origin = data.sections[origin];
        origin_neighbors = data.sections_neighbors[origin];
        section_value = data.sections_values[origin];

        for(j = 0; j < neighbors_l_origin; j++)
        {
            neighbor_section_origin = origin_neighbors[j];
            // only compare origin to neighbors with larger field number
            // this assures that each pair of sections is only compared once, not twice
            if(neighbor_section_origin < origin) { continue; }
            neighbor_section_l = data.sections_l[neighbor_section_origin];
            // ignore sections with less than 2 fields
            if(neighbor_section_l < 2) { continue; }
            neighbor_section = data.sections[neighbor_section_origin];
            bool is_common_origin[8] {0};
            bool is_common_neighbor[8] {0};
            common_fields_l = 0;
            // count how many common fields there are between the two sections
            for(k = 0; k < section_l_origin; k++)
                for(l = 0; l < neighbor_section_l; l++)
                    if(section_origin[k] == neighbor_section[l])
                    {
                        common_fields_l++;
                        is_common_origin[k] = true;
                        is_common_neighbor[l] = true;
                    }
            origin_value = data.sections_values[origin];
            neighbor_value = data.sections_values[neighbor_section_origin];
            // improved condition 1            
            if(neighbor_value == origin_value - section_l_origin + common_fields_l)
            {
                for(k = 0; k < section_l_origin; k++)
                {
                    if(!is_common_origin[k])
                    {
                        success = true;
                        grid.RightClick(section_origin[k]);
                    }
                }
                for(k = 0; k < neighbor_section_l; k++)
                {
                    if(!is_common_neighbor[k])
                    {
                        success = true;
                        grid.LeftClick(neighbor_section[k]);
                    }
                }
            }
            // improved condition 2
            if(origin_value == neighbor_value - neighbor_section_l + common_fields_l)
            {
                for(k = 0; k < neighbor_section_l; k++)
                {
                    if(!is_common_neighbor[k])
                    {
                        success = true;
                        grid.RightClick(neighbor_section[k]);
                    }
                }
                for(k = 0; k < section_l_origin; k++)
                {
                    if(!is_common_origin[k])
                    {
                        success = true;
                        grid.LeftClick(section_origin[k]);
                    }
                }
            }
        }
    }
    return success;
}
