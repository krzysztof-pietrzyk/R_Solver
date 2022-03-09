#include "GridSelfGenerated.hpp"

// w - Width, h - Height, m - Number of mines
GridSelfGenerated::GridSelfGenerated(unsigned short int w, unsigned short int h, unsigned int m) : Grid(w, h, m),
    hash_length(S % 6 > 0 ? (S / 6) + 2 : (S / 6) + 1)
    // each hash symbol encodes 6 fields, 1 more if size is not divisible by 6, 1 more for string terminator
{
    hash = new char[hash_length] {0};

    // 64 consecutive printable ASCII characters
    hash_symbols = new char[64] 
    {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
     ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C', 
     'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
     'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 
     'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 
     'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 
     'l', 'm', 'n', 'o'};
    hash_up_to_date = false;

    zcr_zeros = std::vector<unsigned int>(S, 0);
    zcr_zeros_index = 0;
    zcr_is_zero = std::vector<bool>(S, false);
}

GridSelfGenerated::~GridSelfGenerated()
{
    delete[] hash;
    delete[] hash_symbols;
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

// void GridSelfGenerated::ShowUncovered()
// {
//     for(int i = 0; i < H; i++)
//     {
//         for(int j = 0; j < W; j++)
//         {
//             int f = i * W + j;
//             if(is_flag[f]) cout << "x";
// 			else if(!is_visible[f]) cout << "#";
// 			else if(is_mine[f]) cout << "*";
// 			else if(field_values[f] == 0) cout << " ";
// 			else cout << to_string(field_values[f]);
//         }
//         cout << endl;
//     }
// }

void GridSelfGenerated::CalculateValues()
{
    unsigned char current_field_value;
    unsigned int current_neighbor;
    const unsigned int num_of_not_mines = S - M;
    // Only iterate over non-mine fields
    for(unsigned int & current_field : not_mines)
    {
        current_field_value = 0;
        for_neighbors_of(current_field)
        {
            current_neighbor = neighbors[x];
            // Count how many mines are within each field's neighbors
            if(is_mine[current_neighbor]) current_field_value++;
        }
        field_values[current_field] = current_field_value;
    }
}

void GridSelfGenerated::CalculateHash()
{
    // Return if there's no need to recalculate
    if(hash_up_to_date) return;
    char current_value = 0;
    unsigned int current_symbol_index = 0;
    // Each symbol encodes 6 consequent fields, in terms of mines they contain.
    // It's important to think about the char current_value as a string of bits
    // For example: 00101000 (where 0s are safe and 1s are mines). That value is then 
    // used as an index (in this case 40) in the hash_symbols array to determine the symbol.
    // The hash_symbols array contains 64 consecutive, printable ASCII characters
    for(int i = 0; i < S; i++)
    {
        // Bit shift left
        current_value = current_value << 1;
        // If mine, set the rightmost bit to be 1
        if(is_mine[i]) current_value++;
        // Store the symbol every 6 fields, or if end of map has been reached
        if(i % 6 == 5 || i == S - 1)
        {
            hash[current_symbol_index++] = hash_symbols[current_value];
            current_value = 0;
        }
    }
    hash_up_to_date = true;
}

// protected
void GridSelfGenerated::ZeroChainReaction(unsigned int field)
{
    // Return if called on a non-zero field
    if(field_values[field] != 0) return;

    ClearZCR();
    unsigned int current_zero;
    unsigned int current_neighbor;
    // Clicked field is the beginning of the chain reaction
    zcr_is_zero[field] = true;
    zcr_zeros[zcr_zeros_index++] = field;

    for(unsigned int i = 0; i < zcr_zeros_index; i++)
    {
        // Iterate through each element in zcr_zeros
        // zcr_zeros_index may increase while the loop is running
        // this is why a standard iterator can't be used here
        current_zero = zcr_zeros[i];
        for_neighbors_of(current_zero)
        {
            current_neighbor = neighbors[x];
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
    for(int i = 0; i < zcr_zeros_index; i++) zcr_is_zero[zcr_zeros[i]] = false;
    zcr_zeros_index = 0;
}
