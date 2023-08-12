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

GridHash::GridHash(const uint32_t grid_size_)
{
    const size_t hash_length = CalculateHashLength(grid_size_);
    hash = std::vector<char>(hash_length, 0);
    grid_size = grid_size_;
}

GridHash::GridHash(const GridHash& other)
{
    const size_t hash_length = other.hash.size();
    hash = std::vector<char>(hash_length, 0);
    for(size_t i = 0; i < hash_length; i++)
    {
        hash[i] = other.hash[i];
    }
    grid_size = other.grid_size;
}

GridHash::GridHash(const std::string& new_hash, const uint32_t grid_size_)
{
    const size_t hash_length = new_hash.size();
    hash = std::vector<char>(hash_length, 0);
    for(size_t i = 0; i < hash_length; i++)
    {
        hash[i] = new_hash[i];
    }
    grid_size = grid_size_;
}

GridHash::GridHash(const std::vector<char>& new_hash, const uint32_t grid_size_)
{
    const size_t hash_length = new_hash.size();
    hash = std::vector<char>(hash_length, 0);
    for(size_t i = 0; i < hash_length; i++)
    {
        hash[i] = new_hash[i];
    }
    grid_size = grid_size_;
}

GridHash::GridHash(const CachedVector& mine_positions)
{
    grid_size = mine_positions.MaxSize();
    const size_t hash_length = CalculateHashLength(grid_size);
    hash = std::vector<char>(hash_length, 0);
    CalculateHash(mine_positions);
}

GridHash::~GridHash()
{

}

CachedVector GridHash::GetMinePositions() const
{
    CachedVector mine_positions = CachedVector(grid_size);
    uint32_t current_field = 0;
    const size_t hash_length = hash.size();
    for(size_t i = 0; i < hash_length; i++)
    {
        char current_symbol = hash[i] - ascii_zero;
        if(i < hash_length - 1)
        {
            // All hash symbols except the last
            for(size_t j = 0; j < fields_per_symbol; j++)
            {
                // If the 6th bit of current_symbol is a 1, this field is a mine
                bool is_mine = (current_symbol & is_mine_bit_mask);
                if(is_mine)
                {
                    mine_positions.Add(current_field);
                }
                current_field++;
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
                bool is_mine = (current_symbol & is_mine_bit_mask);
                if(is_mine)
                {
                    mine_positions.Add(current_field);
                }
                current_field++;
                current_symbol = current_symbol << 1;
            }
        }
    }
    return mine_positions;
}

GridHash& GridHash::operator=(const GridHash& other)
{
    if(this == &other)
    {
        return *this;
    }

    const size_t this_hash_length = hash.size();
    const size_t other_hash_length = other.hash.size();
    if(this_hash_length != other_hash_length)
    {
        throw std::invalid_argument("ERROR: GridHash::operator=(const GridHash&) Invalid hash length!");
    }

    for(size_t i = 0; i < other_hash_length; i++)
    {
        hash[i] = other.hash[i];
    }
    return *this;
}

GridHash& GridHash::operator=(const std::string& new_hash)
{
    const size_t this_hash_length = hash.size();
    const size_t new_hash_length = new_hash.size();
    if(this_hash_length != new_hash_length)
    {
        throw std::invalid_argument("ERROR: GridHash::operator=(const std::string&) Invalid hash length!");
    }

    for(size_t i = 0; i < new_hash_length; i++)
    {
        hash[i] = new_hash[i];
    }
    return *this;
}

bool GridHash::operator==(const GridHash& other) const
{
    return hash == other.hash;
}

std::string GridHash::ToString() const
{
    std::string result_string = std::string(hash.begin(), hash.end());
    return result_string;
}

size_t GridHash::Length() const
{
    return hash.size();
}

void GridHash::CalculateHash(const CachedVector& mine_positions)
{
    char current_value = 0;
    size_t current_symbol_index = 0;
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
        if(mine_positions.Contains(i))
        {
            current_value++;
        }
        // Store the symbol every 6 fields, or if end of grid has been reached
        if(symbol_field_counter == fields_per_symbol || i == grid_size - 1)
        {
            hash[current_symbol_index++] = hash_symbols[current_value];
            current_value = 0;
            symbol_field_counter = 0;
        }
    }
}

size_t GridHash::CalculateHashLength(uint32_t grid_size_) const
{
    // each hash symbol encodes 6 fields. 1 more symbol is needed if size is not divisible by 6
    return (grid_size_ % 6 > 0 ? (grid_size_ / 6) + 1 : (grid_size_ / 6));
}
