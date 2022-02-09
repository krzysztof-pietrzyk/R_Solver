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

    zcr_zeros = new unsigned int[S] {0};
    zcr_zeros_index = 0;
    zcr_is_zero = new bool[S] {false};
}

GridSelfGenerated::~GridSelfGenerated()
{
    delete[] hash;
    delete[] hash_symbols;
    delete[] zcr_zeros;
    delete[] zcr_is_zero;
}

void GridSelfGenerated::LeftClick(unsigned int field)
{
    //cout << "Left Click @ " << field << endl;
    if(is_lost) return;
    left_click_counter++;
    is_visible[field] = true;
    visible_fields[visible_fields_index++] = field;
    if(is_mine[field]) is_lost = true; 
    else if(field_values[field] == 0) ZeroChainReaction(field); 
}

void GridSelfGenerated::RightClick(unsigned int field)
{
    //cout << "Right Click @ " << field << endl;
    if(is_lost) return;
    right_click_counter++;
    is_flag[field] = true;
    flags[flags_index++] = field;
}

void GridSelfGenerated::CalculateValues()
{
    unsigned char current_field_value;
    unsigned int current_field;
    unsigned char num_of_neighbors;
    const unsigned int num_of_not_mines = S - M;
    unsigned int* current_field_neighbors;
    // Only iterate over non-mine fields
    for(int i = 0; i < num_of_not_mines; i++)
    {
        current_field_value = 0;
        current_field = not_mines[i];
        num_of_neighbors = neighbors_l[current_field];
        current_field_neighbors = neighbors[current_field];
        for(int j = 0; j < num_of_neighbors; j++)
        {
            // Count how many mines are within each field's neighbors
            if(is_mine[current_field_neighbors[j]]) current_field_value++;
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
    unsigned int* current_neighbors;
    unsigned char current_neighbors_l;
    unsigned int current_zero;
    unsigned int current_neighbor;
    // Clicked field is the beginning of the chain reaction
    zcr_is_zero[field] = true;
    zcr_zeros[zcr_zeros_index++] = field;

    for(int i = 0; i < zcr_zeros_index; i++)
    {
        // Iterate through each element in zcr_zeros
        // zcr_zeros_index may increase while the loop is running
        current_zero = zcr_zeros[i];
        current_neighbors = neighbors[current_zero];
        current_neighbors_l = neighbors_l[current_zero];
        for(int j = 0; j < current_neighbors_l; j++)
        {
            // Iterate through neighbors of current field
            current_neighbor = current_neighbors[j];
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
