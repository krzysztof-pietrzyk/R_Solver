#ifndef Grid_hpp
#define Grid_hpp

#include <cstring>

#define INVALID_GRID_ERROR "ERROR: Grid constructor parameters are invalid."

class Grid
{
    public:

    const unsigned short int W;  // Width
    const unsigned short int H;  // Height
    const unsigned int S;  // Size (Width * Height)
    const unsigned int M;  // Number of mines

    unsigned char* field_values;  // Values of all fields (sorted)

    unsigned int* mines;  // Mine positions (not sorted)
    unsigned int* not_mines;  // Other fields, not mines (not sorted)
    bool* is_mine;  // True if index is a mine (sorted)

    unsigned int* visible_fields;  // Positions of visible fields (not sorted)
    unsigned int visible_fields_index;  // Current count of visible fields
	bool* is_visible;  // True if index is visible (sorted)

    unsigned int* flags;  // Positions of flags (not sorted). Only for the purpose of clearing is_flag array quicker
    unsigned int flags_index;  // Current count of flags
    bool* is_flag;  // True if index is a flag (sorted)

    char* hash;  // String of characters, which uniquely defines the grid (encoded mine positions)
    const unsigned int hash_length;  // Length of hash (constant for given width, height and mines number)
    const char* hash_symbols;  // Possible symbols for hash (constant set)
    bool hash_up_to_date;  // False if CalculateHash has not been called after generating grid

    unsigned int* zcr_zeros;  // Temporary array used in ZeroChainReaction
    unsigned int zcr_zeros_index;  // Temporary index used in ZeroChainReaction
    bool* zcr_is_zero;  // Temporary array used in ZeroChainReaction

    unsigned int** neighbors;  // Array of pointers to positions of neighbors for each field (sorted)
    unsigned char* neighbors_l;  // Number of neighbors of each field (sorted)
    unsigned int* neighbors_large;  // Neighbors array contains pointers to this array

    Grid(unsigned short int w = 9, unsigned short int h = 9, unsigned int m = 10);

    ~Grid();

    void CalculateValues();

    void Clear();

    void CalculateHash();

    protected:

    void ZeroChainReaction(unsigned int field);

    private:

    void FindNeighbors();

    void ClearZCR();

};

#endif
