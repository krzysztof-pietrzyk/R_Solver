#include "AlgorithmRefreshSections.hpp"

AlgorithmRefreshSections::AlgorithmRefreshSections(GridManager& grid_, AlgorithmDataStorage& data_)
    : Algorithm(grid_, data_), double_grid_width(grid_.W * 2)
{
    if(grid.S > 1048575) std::invalid_argument("ERROR: AlgorithmRefreshSections: Grid size must not exceed 1048575 (2^20 - 1) fields!");
    sections_hashes = std::vector<unsigned int>(grid.S, 0);
}

AlgorithmRefreshSections::~AlgorithmRefreshSections() {}

AlgorithmStatus AlgorithmRefreshSections::Run()
{
    Clear();

    const unsigned int border_l = data.border_index;
    const std::vector<unsigned int>& border = data.GetBorder();
    unsigned char section_value_temp = 0;
    unsigned int current_section_hash = 0;
    bool duplicate_temp = false;
    size_t i, j, k = 0;

    // iterate through border fields
    for(i = 0; i < border_l; i++)
    {
        const unsigned int current_border_field = border[i];
        Section& current_section = data.sections[current_border_field];
        current_section.fields_index = 0;
        current_section.neighbors_index = 0;
        section_value_temp = grid.FieldValue(current_border_field);
        current_section_hash = 0;
        // iterate through each border field's neigbors
        for(const unsigned int& neighbor_field : grid.neighbors[current_border_field])
        {
            // count the number of flags already marked around the current_border_field
            if(grid.is_flag[neighbor_field]) { section_value_temp--; continue; }
            // if this neighbor is already visible, ignore it
            else if(grid.is_visible[neighbor_field]) { continue; }
            // add this neighbor to the section
            data.sections[current_border_field].AddField(neighbor_field);
            // encode data about the section into the hash
            if(data.sections[current_border_field].fields_index == 1) { current_section_hash += neighbor_field; }
            else { current_section_hash += GetHashBit(neighbor_field - current_section.fields[0]); }
            // iterate through the neighbors of that neighbor, in order to determine
            // potential neighbour sections of this section
            for(const unsigned int& neighbor_of_neighbor : grid.neighbors[neighbor_field])
            {
                // if this neighbor is not on border or is the currently considered field, ignore it
                if(!data.is_border[neighbor_of_neighbor] || neighbor_of_neighbor == current_border_field) { continue; }
                duplicate_temp = false;
                // iterate through neighbors of this section, which have already been found before
                // in order to filter duplicates
                const size_t current_section_neighbors_index = current_section.neighbors_index;
                for(k = 0; k < current_section_neighbors_index; k++)
                {
                    if(current_section.neighbors[k] == neighbor_of_neighbor)
                    {
                        duplicate_temp = true;
                        break;
                    }
                }
                if(!duplicate_temp) 
                {
                    // only add this to section neighbors if it's not a duplicate
                    current_section.AddNeighbor(neighbor_of_neighbor);
                }
            }
        }
        // Check if section is not a duplicate
        if(CheckHashUnique(current_section_hash))
        {
            // Save all the information about the section
            sections_hashes[data.sections_origins_index] = current_section_hash;
            data.sections_origins[data.sections_origins_index++] = current_border_field;
            data.is_section_origin[current_border_field] = true;
            current_section.value = section_value_temp;
        }
    }

    return AlgorithmStatus::NO_STATUS;
}

void AlgorithmRefreshSections::Clear()
{
    for(size_t i = 0; i < data.sections_origins_index; i++)
    {
        const unsigned int section_origin = data.sections_origins[i];
        data.is_section_origin[section_origin] = false;
        data.sections[section_origin].fields_index = 0;
        data.sections[section_origin].neighbors_index = 0;
    }
    data.sections_origins_index = 0;
}

unsigned int AlgorithmRefreshSections::GetHashBit(unsigned int difference) const
{
	/* This method will only work as intended if the map has less than 1048576 fields

	Abstract structure of a section:

              XXXX 2^20 2^21
    2^22 2^23 2^24 2^25 2^26
    2^27 2^28 2^29 2^30 2^31

    where XXXX means the first field of section in order from left to right and from top to bottom
    it is assured by the section generating code that the first field in the section is XXXX
    summing the numbers assigned to fields relative to field XXXX encodes information about shape of the section in a unique way
    the goal here is to encode all information about the given section within a single 32bit int hash
    with that achieved it is much faster to compare sections between each other and exclude multiple occurences */

    if     (difference == 1)                     return 1048576U;     // 2^20
    else if(difference == 2)                     return 2097152U;     // 2^21
    else if(difference == grid.W - 2)            return 4194304U;     // 2^22
    else if(difference == grid.W - 1)            return 8388608U;     // 2^23
    else if(difference == grid.W)                return 16777216U;    // 2^24
    else if(difference == grid.W + 1)            return 33554432U;    // 2^25
    else if(difference == grid.W + 2)            return 67108864U;    // 2^26
    else if(difference == double_grid_width - 2) return 134217728U;   // 2^27
    else if(difference == double_grid_width - 1) return 268435456U;   // 2^28
    else if(difference == double_grid_width)     return 536870912U;   // 2^29
    else if(difference == double_grid_width + 1) return 1073741824U;  // 2^30
    else if(difference == double_grid_width + 2) return 2147483648U;  // 2^31
    else throw std::invalid_argument("ERROR: AlgorithmRefreshSections::GetHashBit: Impossible section shape!");
}

bool AlgorithmRefreshSections::CheckHashUnique(unsigned int hash) const
{
    const unsigned int number_of_hashes = data.sections_origins_index;
    for(size_t i = 0; i < number_of_hashes; i++)
    {
        if(sections_hashes[i] == hash) return false;
    }
    return true;
}
