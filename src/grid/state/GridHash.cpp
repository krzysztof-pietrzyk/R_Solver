// implemented header
#include "GridHash.hpp"

// project includes
#include "../../utils/CachedVector.hpp"
#include "../../utils/Logger.hpp"

// std includes
#include <iomanip>


const uint8_t GridHash::max_consecutive_symbols = 15;
const uint8_t GridHash::fields_per_symbol = 6;
const uint8_t GridHash::hashing_bit_mask = 32;

GridHash::GridHash(const CachedVector& layer)
{
    hash = std::vector<char>();
    grid_size = layer.MaxSize();
    CalculateHash(layer);
}

GridHash::GridHash(const GridHash& other)
{
    grid_size = other.grid_size;
    hash = std::vector<char>(other.hash);
}

GridHash::GridHash(const std::string& new_hash, uint32_t _grid_size)
{
    grid_size = _grid_size;
    hash = RestoreConsecutiveZerosOnes(new_hash);
}

GridHash::GridHash()
{
    grid_size = 0;
    hash = std::vector<char>();
}

GridHash::~GridHash()
{

}

CachedVector GridHash::Unhash() const
{
    CachedVector unhashed_layer = CachedVector(grid_size);
    uint32_t current_field = 0;
    const size_t hash_length = hash.size();
    for(size_t i = 0; i < hash_length - 1; i++)
    {
        // Handling all hash symbols except the last
        char current_pattern = symbols_to_patterns.at(hash[i]);
        for(size_t j = 0; j < fields_per_symbol; j++)
        {
            // If the 6th bit of current_pattern is a 1, this field is a mine
            bool is_mine = (current_pattern & hashing_bit_mask);
            if(is_mine)
            {
                unhashed_layer.Add(current_field);
            }
            current_field++;
            // Bit shift current_pattern once to the left
            current_pattern = current_pattern << 1;
        }
    }
    // Handling the last hash symbol
    char last_pattern = symbols_to_patterns.at(hash.back());
    // Figure out how many fields the last symbol encodes
    const uint8_t grid_size_mod_6 = grid_size % fields_per_symbol;
    // Can be anywhere from 1 to 6. If it's a 0, it means the grid size is perfectly divisible into
    // chunks of 6 fields, so the last symbol encodes full 6 fields, just like the other symbols
    // Otherwise, it only encodes 1, 2, 3, 4 or 5 fields
    const uint8_t last_symbol_length = grid_size_mod_6 == 0 ? fields_per_symbol : grid_size_mod_6;
    // Bit shift the symbol to skip the unused bits if necessary
    // In case when last_symbol_length is 6, it bit shifts 0 times
    last_pattern = last_pattern << (fields_per_symbol - last_symbol_length);

    for(size_t j = 0; j < last_symbol_length; j++)
    {
        // Now the symbol is handled exactly the same as all others
        bool is_mine = (last_pattern & hashing_bit_mask);
        if(is_mine)
        {
            unhashed_layer.Add(current_field);
        }
        current_field++;
        last_pattern = last_pattern << 1;
    }
    return unhashed_layer;
}

std::string GridHash::String() const
{
    return OptimizeConsecutiveZerosOnes(hash);
}

GridHash& GridHash::operator=(const GridHash& other)
{
    grid_size = other.grid_size;
    hash = std::vector<char>(other.hash);
    return *this;
}

bool GridHash::operator==(const GridHash& other) const
{
    return hash == other.hash && grid_size == other.grid_size;
}

void GridHash::CalculateHash(const CachedVector& layer)
{
    char current_value = 0;
    size_t current_symbol_index = 0;
    uint8_t symbol_field_counter = 0;
    hash.clear();
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
        if(layer.Contains(i))
        {
            current_value++;
        }
        // Store the symbol every 6 fields, or if end of grid has been reached
        if(symbol_field_counter == fields_per_symbol || i == grid_size - 1)
        {
            hash.push_back(patterns_to_symbols.at(current_value));
            current_value = 0;
            symbol_field_counter = 0;
        }
    }
}

std::string GridHash::OptimizeConsecutiveZerosOnes(const std::vector<char>& hash_to_optimize) const
{
    std::ostringstream output;
    uint32_t zero_counter = 0U;
    uint32_t one_counter = 0U;

    for(const char& hash_char : hash_to_optimize)
    {
        if(hash_char == '0')
        {
            if(one_counter > 0U)
            {
                output << consecutive_ones_to_symbols.at(one_counter);
                one_counter = 0U;
            }
            zero_counter++;
            if(zero_counter == max_consecutive_symbols)
            {
                output << consecutive_zeros_to_symbols.at(zero_counter);
                zero_counter = 0U;
            }
        }
        else if(hash_char == '1')
        {
            if(zero_counter > 0U)
            {
                output << consecutive_zeros_to_symbols.at(zero_counter);
                zero_counter = 0U;
            }
            one_counter++;
            if(one_counter == max_consecutive_symbols)
            {
                output << consecutive_ones_to_symbols.at(one_counter);
                one_counter = 0U;
            }
        }
        else
        {
            if(one_counter > 0U)
            {
                output << consecutive_ones_to_symbols.at(one_counter);
            }
            else if(zero_counter > 0U)
            {
                output << consecutive_zeros_to_symbols.at(zero_counter);
            }
            zero_counter = 0U;
            one_counter = 0U;
            output << hash_char;
        }
    }
    if(one_counter > 0U)
    {
        output << consecutive_ones_to_symbols.at(one_counter);
    }
    else if(zero_counter > 0U)
    {
        output << consecutive_zeros_to_symbols.at(zero_counter);
    }
    return output.str();
}

std::vector<char> GridHash::RestoreConsecutiveZerosOnes(const std::string& hash_to_restore) const
{
    std::ostringstream temp;

    for(const char& hash_char : hash_to_restore)
    {
        auto consecutive_zero = symbols_to_consecutive_zeros.find(hash_char);
        if(consecutive_zero != symbols_to_consecutive_zeros.end())
        {
            temp << std::string(consecutive_zero->second, '0');
            continue;
        }
        auto consecutive_one = symbols_to_consecutive_ones.find(hash_char);
        if(consecutive_one != symbols_to_consecutive_ones.end())
        {
            temp << std::string(consecutive_one->second, '1');
            continue;
        }
        temp << hash_char;
    }

    std::string result = temp.str();
    return std::vector<char>(result.begin(), result.end());
}
