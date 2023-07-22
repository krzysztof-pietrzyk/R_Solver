#include "GridSelfGenerated.hpp"

// w - Width, h - Height, m - Number of mines
GridSelfGenerated::GridSelfGenerated(uint16_t w, uint16_t h, uint32_t m)
    : Grid(w, h, m), hash(GridHash(S))
{
    zcr_zeros = std::vector<uint32_t>(S, 0);
    zcr_zeros_index = 0;
    zcr_is_zero = std::vector<bool>(S, false);

    statistics_field_types = new StatisticsCollectorFieldTypes();
    statistics_collectors.push_back(statistics_field_types);
}

GridSelfGenerated::~GridSelfGenerated()
{

}

bool GridSelfGenerated::LeftClick(uint32_t field)
{
    if(is_visible[field] || is_lost)
    {
        return false;
    }
    left_click_counter++;
    is_visible[field] = true;
    visible_fields[visible_fields_index++] = field;
    if(is_mine[field])
    {
        is_lost = true;
    } 
    else if(field_values[field] == 0) ZeroChainReaction(field);
    return true;
}

bool GridSelfGenerated::RightClick(uint32_t field)
{
    if(is_flag[field] || is_lost)
    {
        return false;
    }
    right_click_counter++;
    is_flag[field] = true;
    flags[flags_index++] = field;
    return true;
}

void GridSelfGenerated::CalculateValues()
{
    uint8_t current_field_value;
    // Only iterate over non-mine fields
    for(const uint32_t& current_field : not_mines)
    {
        current_field_value = 0;
        for(const uint32_t& current_neighbor : neighbors[current_field])
        {
            // Count how many mines are within each field's neighbors
            if(is_mine[current_neighbor]) current_field_value++;
        }
        field_values[current_field] = current_field_value;
    }

    // Set all mine fields to value 9 to avoid "trashy data"
    for(const uint32_t& current_field : mines)
    {
        field_values[current_field] = 9;
    }

    statistics_field_types->CountFieldTypes(field_values);
}

void GridSelfGenerated::CalculateHash()
{
    hash.CalculateHash(is_mine);
}

// protected
void GridSelfGenerated::ZeroChainReaction(uint32_t field)
{
    // Return if called on a non-zero field
    if(field_values[field] != 0) return;

    ClearZCR();
    // Clicked field is the beginning of the chain reaction
    zcr_is_zero[field] = true;
    zcr_zeros[zcr_zeros_index++] = field;

    for(size_t i = 0; i < zcr_zeros_index; i++)
    {
        // Iterate through each element in zcr_zeros
        // zcr_zeros_index may increase while the loop is running
        // this is why a standard iterator can't be used here
        const uint32_t current_zero = zcr_zeros[i];
        for(const uint32_t& current_neighbor : neighbors[current_zero])
        {
            // Iterate through neighbors of current field
            if(!is_visible[current_neighbor])
            {
                is_visible[current_neighbor] = true;
                visible_fields[visible_fields_index++] = current_neighbor;
                if(field_values[current_neighbor] == 0 && !zcr_is_zero[current_neighbor])
                {
                    zcr_is_zero[current_neighbor] = true;
                    zcr_zeros[zcr_zeros_index++] = current_neighbor;
                }
            }
        }
    }
}

// private
void GridSelfGenerated::ClearZCR()
{
    // Clear the temporary array and zero the index
    zcr_is_zero.assign(S, false);
    zcr_zeros_index = 0;
}

#ifdef DEBUG_MODE_PRINT
#include <iostream>
using namespace std;

void GridSelfGenerated::PrintUncovered() const
{
    for(size_t i = 0; i < H; i++)
    {
        for(size_t j = 0; j < W; j++)
        {
            const uint32_t f = i * W + j;
            if(is_flag[f]) cout << ".";
            else if(is_visible[f])
            {
                if(field_values[f] == 0) cout << " ";
                else if(is_mine[f]) cout << "!";
                else cout << int(field_values[f]);
            } 
            else cout << "#";
        }
        cout << endl;
    }
    cout << hash.ToString() << endl;
}
#endif
