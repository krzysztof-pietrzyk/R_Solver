#ifndef GRID_HASH_HPP
#define GRID_HASH_HPP

#include "../utils/CachedVector.hpp"
#include "../utils/Logger.hpp"

#include <string>

class GridHash
{
    public:

    GridHash(const uint32_t grid_size);
    GridHash(const GridHash& other);
    GridHash(const std::string& new_hash, const uint32_t grid_size_);
    GridHash(const std::vector<char>& new_hash, const uint32_t grid_size_);
    GridHash(const CachedVector& mine_positions);
    ~GridHash();

    CachedVector GetMinePositions() const;
    std::string ToString() const;
    size_t Length() const;

    GridHash& operator=(const GridHash& other);
    GridHash& operator=(const std::string& new_hash);
    bool operator==(const GridHash& other) const;

    private:

    std::vector<char> hash;
    uint32_t grid_size;

    static const std::vector<char> hash_symbols;
    static const uint8_t fields_per_symbol;
    static const uint8_t is_mine_bit_mask;
    static const char ascii_zero;

    void CalculateHash(const CachedVector& mine_positions);
    size_t CalculateHashLength(uint32_t grid_size) const;
};

#endif
