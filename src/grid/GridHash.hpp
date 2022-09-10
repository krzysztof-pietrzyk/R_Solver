#ifndef GridHash_hpp
#define GridHash_hpp

#include <vector>
#include <string>
#include <stdexcept>

class GridHash
{
    public:

    GridHash(const unsigned int grid_size);

    GridHash(const GridHash& other);

    GridHash(std::string new_hash);

    GridHash(const std::vector<char> new_hash);

    ~GridHash();

    // From mine_positions vector
    void CalculateHash(const std::vector<unsigned int> mine_positions, const unsigned int grid_size);

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

    static const unsigned char fields_per_symbol;

    static const unsigned char is_mine_bit_mask;

    static const char ascii_zero;
};

#endif
