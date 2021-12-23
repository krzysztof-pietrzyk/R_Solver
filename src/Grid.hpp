#ifndef Grid_hpp
#define Grid_hpp

#include <cstring>
#include <stdexcept>

#include "GridManager.hpp"

class Grid : public GridManager
{
    public:

    unsigned int* mines;  // Mine positions (not sorted)
    unsigned int* not_mines;  // Other fields, not mines (not sorted)
    bool* is_mine;  // True if index is a mine (sorted)

    unsigned int* neighbors_large;  // Neighbors array contains pointers to this array

    Grid(unsigned short int w, unsigned short int h, unsigned int m);

    ~Grid();

    void Clear();

    private:

    void FindNeighbors();
};

#endif
