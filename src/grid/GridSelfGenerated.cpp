#include "GridSelfGenerated.hpp"

// w - Width, h - Height, m - Number of mines
GridSelfGenerated::GridSelfGenerated(unsigned short int w, unsigned short int h, unsigned int m)
    : Grid(w, h, m), hash(GridHash(S))
{
    zcr_zeros = std::vector<unsigned int>(S, 0);
    zcr_zeros_index = 0;
    zcr_is_zero = std::vector<bool>(S, false);
}

GridSelfGenerated::~GridSelfGenerated()
{

}

void GridSelfGenerated::LeftClick(unsigned int field)
{
    // cout << "Left Click @ " << field << endl;
    if(is_lost) return;
    if(is_visible[field]) return;
    left_click_counter++;
    is_visible[field] = true;
    visible_fields[visible_fields_index++] = field;
    if(is_mine[field])
    {
        is_lost = true; 
        //cout << "LOST: " << field << endl;
    } 
    else if(field_values[field] == 0) ZeroChainReaction(field); 
}

void GridSelfGenerated::RightClick(unsigned int field)
{
    // cout << "Right Click @ " << field << endl;
    if(is_lost) return;
    if(is_flag[field]) return;
    right_click_counter++;
    is_flag[field] = true;
    flags[flags_index++] = field;
}

void GridSelfGenerated::CalculateValues()
{
    unsigned char current_field_value;
    unsigned int current_neighbor;
    const unsigned int num_of_not_mines = S - M;
    // Only iterate over non-mine fields
    for(const unsigned int& current_field : not_mines)
    {
        current_field_value = 0;
        for(const unsigned int& current_neighbor : neighbors[current_field])
        {
            // Count how many mines are within each field's neighbors
            if(is_mine[current_neighbor]) current_field_value++;
        }
        field_values[current_field] = current_field_value;
    }
}

void GridSelfGenerated::CalculateHash()
{
    hash.CalculateHash(is_mine);
}

// protected
void GridSelfGenerated::ZeroChainReaction(unsigned int field)
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
        const unsigned int current_zero = zcr_zeros[i];
        for(const unsigned int& current_neighbor : neighbors[current_zero])
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

// #include <iostream>
// using namespace std;

// void GridSelfGenerated::PrintUncovered()
// {
//     for(size_t i = 0; i < H; i++)
//     {
//         for(size_t j = 0; j < W; j++)
//         {
//             const unsigned int f = i * W + j;
//             if(is_flag[f]) cout << ".";
//             else if(is_visible[f])
//             {
//                 if(field_values[f] == 0) cout << " ";
//                 else cout << int(field_values[f]);
//             } 
//             else cout << "#";
//         }
//         cout << endl;
//     }
//     cout << endl;
// }
