#include "AlgorithmLayerTwo.hpp"

AlgorithmLayerTwo::AlgorithmLayerTwo(GridManager& grid_, AlgorithmDataStorage& data_) : AlgorithmAction(grid_, data_) {}

AlgorithmLayerTwo::~AlgorithmLayerTwo() {}

AlgorithmStatus AlgorithmLayerTwo::RunInternal()
{
    const unsigned int sections_l = data.sections_origins_index;
    bool success = false;
    unsigned char common_fields_l = 0;
    const size_t max_section_length = 8;
    std::vector<bool> is_common_origin = std::vector<bool>(max_section_length, false);
    std::vector<bool> is_common_neighbor = std::vector<bool>(max_section_length, false);

    size_t i, j, k, l = 0;
    for(i = 0; i < sections_l; i++)
    {
        const unsigned int origin = data.sections_origins[i];
        const Section& current_section = data.sections[origin];
        const size_t current_section_neighbors_l = current_section.neighbors_index;
        // ignore sections that have no neighbors
        if(current_section_neighbors_l == 0) { continue; }
        const size_t current_section_l = current_section.fields_index;
        // ignore sections with less than 2 fields
        if(current_section_l < 2) { continue; }
        const unsigned char section_value = current_section.value;

        for(j = 0; j < current_section_neighbors_l; j++)
        {
            const unsigned int neighbor_section_origin = current_section.neighbors[j];
            const Section& neighbor_section = data.sections[neighbor_section_origin];
            // only consider neighbors which are actual section origins
            if(!data.is_section_origin[neighbor_section_origin]) { continue; }
            // only compare origin to neighbors with larger field number
            // this assures that each pair of sections is only compared once, not twice
            if(neighbor_section_origin < origin) { continue; }
            const size_t neighbor_section_l = neighbor_section.fields_index;
            // ignore sections with less than 2 fields
            if(neighbor_section_l < 2) { continue; }
            // clear the temporary vectors
            std::fill(is_common_origin.begin(), is_common_origin.end(), false);
            std::fill(is_common_neighbor.begin(), is_common_neighbor.end(), false);
            common_fields_l = 0;
            // count how many common fields there are between the two sections
            for(k = 0; k < current_section_l; k++)
                for(l = 0; l < neighbor_section_l; l++)
                    if(current_section.fields[k] == neighbor_section.fields[l])
                    {
                        common_fields_l++;
                        is_common_origin[k] = true;
                        is_common_neighbor[l] = true;
                    }
            const unsigned char currents_section_value = current_section.value;
            const unsigned char neighbor_section_value = neighbor_section.value;
            // improved condition 1            
            if(neighbor_section_value == currents_section_value - current_section_l + common_fields_l)
            {
                for(k = 0; k < current_section_l; k++)
                {
                    if(!is_common_origin[k])
                    {
                        success = true;
                        grid.RightClick(current_section.fields[k]);
                    }
                }
                for(k = 0; k < neighbor_section_l; k++)
                {
                    if(!is_common_neighbor[k])
                    {
                        success = true;
                        grid.LeftClick(neighbor_section.fields[k]);
                    }
                }
            }
            // improved condition 2
            if(currents_section_value == neighbor_section_value - neighbor_section_l + common_fields_l)
            {
                for(k = 0; k < neighbor_section_l; k++)
                {
                    if(!is_common_neighbor[k])
                    {
                        success = true;
                        grid.RightClick(neighbor_section.fields[k]);
                    }
                }
                for(k = 0; k < current_section_l; k++)
                {
                    if(!is_common_origin[k])
                    {
                        success = true;
                        grid.LeftClick(current_section.fields[k]);
                    }
                }
            }
        }
    }
    if(success) { return AlgorithmStatus::SUCCESS; }
    return AlgorithmStatus::NO_MOVES;
}
