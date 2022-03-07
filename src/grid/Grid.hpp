#ifndef Grid_hpp
#define Grid_hpp

#include <cstring>
#include <stdexcept>

#include "GridManager.hpp"

class Grid : public GridManager
{
    public:

    std::vector<unsigned int> mines;  // Mine positions (not sorted)
    std::vector<unsigned int> not_mines;  // Other fields, not mines (not sorted)
    std::vector<bool> is_mine;  // True if index is a mine (sorted)

    Grid(unsigned short int w, unsigned short int h, unsigned int m);

    ~Grid();

    void Clear();

    private:

    void FindNeighbors();
};

#endif
