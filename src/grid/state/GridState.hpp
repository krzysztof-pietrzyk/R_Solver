#ifndef GRID_STATE_HPP
#define GRID_STATE_HPP

// project includes
#include "GridHash.hpp"
#include "../../utils/CachedVector.hpp"

// std includes

// forward declarations


class GridState
{
    // If reading Grid state from an image is ever to be implemented, 
    // this class needs to be extended with another class that will handle field values
    public:

    GridState();
    GridState(const CachedVector& mines);
    GridState(const CachedVector& mines, const CachedVector& flagged, const CachedVector& visible);
    GridState(const std::string& state);
    ~GridState();

    std::string String() const;
    CachedVector GetMines() const;
    CachedVector GetFlagged() const;
    CachedVector GetVisible() const;
    bool GetIsLost() const;

    GridState& operator=(const GridState& other);
    bool operator==(const GridState& other) const;

    static const CachedVector unspecified_layer;

    private:

    GridHash hash_mines;
    GridHash hash_flagged;
    GridHash hash_visible;
    bool is_lost;
    uint32_t grid_size;

    static const char separator_symbol;
    static const size_t expected_num_of_separators;
    static const GridHash unspecified_layer_hash;
    static const char lost_symbol;
    static const char not_lost_symbol;

    char GetIsLostSymbol() const;
    void SetIsLost(char symbol);
};

#endif
