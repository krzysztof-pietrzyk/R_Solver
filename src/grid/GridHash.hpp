#ifndef GRID_HASH_HPP
#define GRID_HASH_HPP

#include <vector>
#include <string>
#include <stdexcept>

class GridHash
{
    public:

    GridHash(const uint32_t grid_size);

    GridHash(const GridHash& other);

    GridHash(std::string new_hash);

    GridHash(const std::vector<char> new_hash);

    ~GridHash();

    // From mine_positions vector
    void CalculateHash(const std::vector<uint32_t> mine_positions, const uint32_t grid_size);

    // From is_mine vector
    virtual void CalculateHash(const std::vector<bool> is_mine);

    // For is_mine vector
    void GetMines(std::vector<bool>& is_mine);

    void operator=(const GridHash& other);

    void operator=(std::string new_hash);

    std::string ToString();

    void SetUpToDate(const bool up_to_date);

    size_t Length();

    private:

    std::vector<char> hash;

    bool is_up_to_date;

    static const std::vector<char> hash_symbols;

    static const uint8_t fields_per_symbol;

    static const uint8_t is_mine_bit_mask;

    static const char ascii_zero;
};

#endif
