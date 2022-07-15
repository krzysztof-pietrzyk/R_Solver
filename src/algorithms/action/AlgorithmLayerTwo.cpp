#include "AlgorithmLayerTwo.hpp"

AlgorithmLayerTwo::AlgorithmLayerTwo(GridManager& grid_, AlgorithmDataStorage& data_) : AlgorithmAction(grid_, data_) {}

AlgorithmLayerTwo::~AlgorithmLayerTwo() {}

AlgorithmStatus AlgorithmLayerTwo::RunInternal()
{
    const unsigned int sections_l = data.sections_origins_index;
    bool success = false;
    unsigned char common_fields_l = 0;
    size_t i, j, k, l = 0;
    
    for(i = 0; i < sections_l; i++)
    {
        const unsigned int origin = data.sections_origins[i];
        const unsigned char neighbors_l_origin = data.sections_neighbors_l[origin];
        // ignore sections that have no neighbors
        if(neighbors_l_origin == 0) { continue; }
        const unsigned char section_l_origin = data.sections_l[origin];
        // ignore sections with less than 2 fields
        if(section_l_origin < 2) { continue; }

        const unsigned int section_origin_offset = origin * MAX_SECTION_LENGTH;
        const unsigned int origin_neighbors_offset = origin * MAX_SECTION_NEIGHBORS;
        const unsigned char section_value = data.sections_values[origin];

        for(j = 0; j < neighbors_l_origin; j++)
        {
            const unsigned int neighbor_section_origin = data.sections_neighbors[origin_neighbors_offset + j];
            // only consider neighbors which are actual section origins
            if(!data.is_section_origin[neighbor_section_origin]) { continue; }
            // only compare origin to neighbors with larger field number
            // this assures that each pair of sections is only compared once, not twice
            if(neighbor_section_origin < origin) { continue; }
            const unsigned char neighbor_section_l = data.sections_l[neighbor_section_origin];
            // ignore sections with less than 2 fields
            if(neighbor_section_l < 2) { continue; }
            const unsigned int neighbor_section_offset = neighbor_section_origin * MAX_SECTION_LENGTH;
            bool is_common_origin[8] {0};
            bool is_common_neighbor[8] {0};
            common_fields_l = 0;
            // count how many common fields there are between the two sections
            for(k = 0; k < section_l_origin; k++)
                for(l = 0; l < neighbor_section_l; l++)
                    if(data.sections[section_origin_offset + k] == data.sections[neighbor_section_offset + l])
                    {
                        common_fields_l++;
                        is_common_origin[k] = true;
                        is_common_neighbor[l] = true;
                    }
            const unsigned char origin_value = data.sections_values[origin];
            const unsigned char neighbor_value = data.sections_values[neighbor_section_origin];
            // improved condition 1            
            if(neighbor_value == origin_value - section_l_origin + common_fields_l)
            {
                for(k = 0; k < section_l_origin; k++)
                {
                    if(!is_common_origin[k])
                    {
                        success = true;
                        grid.RightClick(data.sections[section_origin_offset + k]);
                    }
                }
                for(k = 0; k < neighbor_section_l; k++)
                {
                    if(!is_common_neighbor[k])
                    {
                        success = true;
                        grid.LeftClick(data.sections[neighbor_section_offset + k]);
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
                        grid.RightClick(data.sections[neighbor_section_offset + k]);
                    }
                }
                for(k = 0; k < section_l_origin; k++)
                {
                    if(!is_common_origin[k])
                    {
                        success = true;
                        grid.LeftClick(data.sections[section_origin_offset + k]);
                    }
                }
            }
        }
    }
    if(success) { return AlgorithmStatus::SUCCESS; }
    return AlgorithmStatus::NO_MOVES;
}
