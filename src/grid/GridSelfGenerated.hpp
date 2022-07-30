#ifndef GridSelfGenerated_hpp
#define GridSelfGenerated_hpp

#include "Grid.hpp"
#include "GridHash.hpp"

class GridSelfGenerated : public Grid
{
    public:

    GridHash hash;

    GridSelfGenerated(unsigned short int w, unsigned short int h, unsigned int m);

    ~GridSelfGenerated();

    void LeftClick(unsigned int field);

    void RightClick(unsigned int field);

    void CalculateHash();

    void CalculateValues();

    // void PrintUncovered();

    protected:

    std::vector<unsigned int> zcr_zeros;  // Temporary array used in ZeroChainReaction
    unsigned int zcr_zeros_index;  // Temporary index used in ZeroChainReaction
    std::vector<bool> zcr_is_zero;  // Temporary array used in ZeroChainReaction

    void ZeroChainReaction(unsigned int field);

    void ClearZCR();
};

#endif
