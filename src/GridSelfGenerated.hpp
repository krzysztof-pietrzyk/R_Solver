#ifndef GridSelfGenerated_hpp
#define GridSelfGenerated_hpp

#include "Grid.hpp"

class GridSelfGenerated : public Grid
{
    public:

    char* hash;  // String of characters, which uniquely defines the grid (encoded mine positions)
    const unsigned int hash_length;  // Length of hash (constant for given width, height and mines number)
    const char* hash_symbols;  // Possible symbols for hash (constant set)
    bool hash_up_to_date;  // False if CalculateHash has not been called after generating grid

    unsigned int* zcr_zeros;  // Temporary array used in ZeroChainReaction
    unsigned int zcr_zeros_index;  // Temporary index used in ZeroChainReaction
    bool* zcr_is_zero;  // Temporary array used in ZeroChainReaction

    GridSelfGenerated(unsigned short int w, unsigned short int h, unsigned int m);

    ~GridSelfGenerated();

    void LeftClick(unsigned int field);

    void RightClick(unsigned int field);

    //void ShowUncovered();

    void CalculateHash();

    void CalculateValues();

    protected:

    void ZeroChainReaction(unsigned int field);

    private:

    void ClearZCR();
};

#endif
