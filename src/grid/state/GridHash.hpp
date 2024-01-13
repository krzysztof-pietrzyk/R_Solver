#ifndef GRID_HASH_HPP
#define GRID_HASH_HPP

// project includes

// std includes
#include <string>
#include <vector>
#include <map>

// forward declarations
class CachedVector;
struct GridDimensions;


class GridHash
{
    public:

    static const uint8_t max_consecutive_symbols;
    static const uint8_t fields_per_symbol;

    GridHash(const CachedVector& layer);
    GridHash(const GridHash& other);
    GridHash(const std::string& new_hash, uint32_t _grid_size);
    GridHash();
    ~GridHash();

    CachedVector Unhash() const;
    std::string String() const;

    GridHash& operator=(const GridHash& other);
    bool operator==(const GridHash& other) const;

    private:

    std::vector<char> hash;
    uint32_t grid_size;

    static const std::map<char, char> symbols_to_patterns;
    static const std::map<char, char> patterns_to_symbols;
    static const std::map<char, char> consecutive_zeros_to_symbols;
    static const std::map<char, char> symbols_to_consecutive_zeros;
    static const std::map<char, char> consecutive_ones_to_symbols;
    static const std::map<char, char> symbols_to_consecutive_ones;
    static const uint8_t hashing_bit_mask;

    void CalculateHash(const CachedVector& layer);
    std::string OptimizeConsecutiveZerosOnes(const std::vector<char>& hash_to_optimize) const;
    std::vector<char> RestoreConsecutiveZerosOnes(const std::string& hash_to_restore) const;
};

#endif
