#include "GridHash.hpp"

// 64 consecutive printable ASCII characters
const std::vector<char> GridHash::hash_symbols =
{
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C', 
    'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 
    'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 
    'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 
    'l', 'm', 'n', 'o'
};

const uint8_t GridHash::fields_per_symbol = 6;

const uint8_t GridHash::is_mine_bit_mask = 32;

const char GridHash::ascii_zero = '0';

GridHash::GridHash(const uint32_t grid_size)
{
    // each hash symbol encodes 6 fields, 1 more if size is not divisible by 6
    const size_t hash_length = grid_size % 6 > 0 ? (grid_size / 6) + 1 : (grid_size / 6);
    hash = std::vector<char>(hash_length, 0);
    is_up_to_date = false;
}

GridHash::GridHash(const GridHash& other)
{
    const size_t hash_length = other.hash.size();
    hash = std::vector<char>(hash_length, 0);
    for(size_t i = 0; i < hash_length; i++)
    {
        hash[i] = other.hash[i];
    }
    is_up_to_date = true;
}

GridHash::GridHash(std::string new_hash)
{
    const size_t hash_length = new_hash.size();
    hash = std::vector<char>(hash_length, 0);
    for(size_t i = 0; i < hash_length; i++)
    {
        hash[i] = new_hash[i];
    }
    is_up_to_date = true;
}

GridHash::GridHash(const std::vector<char> new_hash)
{
    const size_t hash_length = new_hash.size();
    hash = std::vector<char>(hash_length, 0);
    for(size_t i = 0; i < hash_length; i++)
    {
        hash[i] = new_hash[i];
    }
    is_up_to_date = true;
}

GridHash::~GridHash()
{

}

void GridHash::CalculateHash(const std::vector<uint32_t> mine_positions, const uint32_t grid_size)
{
    // Return if there's no need to recalculate
    if(is_up_to_date) return;
    // Create a temporary vector similar to is_mine
    std::vector<bool> is_mine_temp = std::vector<bool>(grid_size, false);
    const size_t number_of_mines = mine_positions.size();
    for(size_t i = 0; i < number_of_mines; i++)
    {
        const uint32_t current_mine_position = mine_positions[i];
        if(current_mine_position >= grid_size)
        {
            throw std::invalid_argument("ERROR: GridHash: Mine out of bounds!");
        }
        is_mine_temp[current_mine_position] = true;
    }
    // Use the calculation implementation for is_mine vector
    CalculateHash(is_mine_temp);
}

void GridHash::CalculateHash(const std::vector<bool> is_mine)
{
    // Return if there's no need to recalculate
    if(is_up_to_date) return;
    char current_value = 0;
    size_t current_symbol_index = 0;
    const size_t grid_size = is_mine.size();
    uint8_t symbol_field_counter = 0;
    // Each symbol encodes 6 consequent fields, in terms of mines they contain.
    // It's important to think about the char current_value as a string of bits
    // For example: 00101000 (where 0s are safe and 1s are mines). That value is then 
    // used as an index (in this case 40) in the hash_symbols array to determine the symbol.
    // The hash_symbols array contains 64 consecutive, printable ASCII characters
    for(size_t i = 0; i < grid_size; i++)
    {
        symbol_field_counter++;
        // Bit shift left
        current_value = current_value << 1;
        // If mine, set the rightmost bit to be 1
        if(is_mine[i]) { current_value++; }
        // Store the symbol every 6 fields, or if end of map has been reached
        if(symbol_field_counter == fields_per_symbol || i == grid_size - 1)
        {
            hash[current_symbol_index++] = hash_symbols[current_value];
            current_value = 0;
            symbol_field_counter = 0;
        }
    }
    is_up_to_date = true;
}

void GridHash::GetMines(std::vector<bool>& is_mine)
{
    if(!is_up_to_date)
    {
        throw std::invalid_argument("ERROR: GridHash: Attempting to get mines from an expired hash!");
    }
    uint32_t current_field = 0;
    const size_t grid_size = is_mine.size();
    const size_t hash_length = hash.size();
    for(size_t i = 0; i < hash_length; i++)
    {
        char current_symbol = hash[i] - ascii_zero;
        if(i < hash_length - 1)
        {
            // All hash symbols except the last
            for(size_t j = 0; j < 6; j++)
            {
                // If the 6th bit of current_symbol is a 1, this field is a mine
                is_mine[current_field++] = (current_symbol & is_mine_bit_mask);
                // Bit shift current_symbol once to the left
                current_symbol = current_symbol << 1;
            }
        }
        else
        {
            // Handling the last hash symbol
            // Figure out how many fields the last symbol encodes
            const uint8_t grid_size_mod_6 = grid_size % fields_per_symbol;
            // Can be anywhere from 1 to 6. If it's a 0, it means the grid size is perfectly divisible into
            // chunks of 6 fields, so the last symbol encodes full 6 fields, just like the other symbols
            // Otherwise, it only encodes 1, 2, 3, 4 or 5 fields
            const uint8_t last_symbol_length = grid_size_mod_6 == 0 ? fields_per_symbol : grid_size_mod_6;
            // Bit shift the symbol to skip the unused bits if necessary
            // In case when last_symbol_length is 6, it bit shifts 0 times
            current_symbol = current_symbol << (fields_per_symbol - last_symbol_length);

            for(size_t j = 0; j < last_symbol_length; j++)
            {
                // Now the symbol is handled exactly the same as all others
                is_mine[current_field++] = (current_symbol & is_mine_bit_mask);
                current_symbol = current_symbol << 1;
            }
        }
    }
}

void GridHash::operator=(const GridHash& other)
{
    const size_t this_hash_length = hash.size();
    const size_t other_hash_length = other.hash.size();
    if(this_hash_length != other_hash_length)
    {
        throw std::invalid_argument("ERROR: GridHash: Invalid hash length! (const GridHash& other)");
    }
    for(size_t i = 0; i < other_hash_length; i++)
    {
        hash[i] = other.hash[i];
    }
    is_up_to_date = true;
}

void GridHash::operator=(std::string new_hash)
{
    const size_t this_hash_length = hash.size();
    const size_t new_hash_length = new_hash.size();
    if(this_hash_length != new_hash_length)
    {
        throw std::invalid_argument("ERROR: GridHash: Invalid hash length! (std::string new_hash)");
    }
    for(size_t i = 0; i < new_hash_length; i++)
    {
        hash[i] = new_hash[i];
    }
    is_up_to_date = true;
}

std::string GridHash::ToString()
{
    std::string result_string = std::string(hash.begin(), hash.end());
    return result_string;
}

void GridHash::SetUpToDate(const bool up_to_date)
{
    this->is_up_to_date = up_to_date;
}

size_t GridHash::Length()
{
    return hash.size();
}
