#ifndef GRID_HPP
#define GRID_HPP

#include <cstring>
#include <stdexcept>

#include "GridManager.hpp"

class Grid : public GridManager
{
    public:

    std::vector<uint32_t> mines;  // Mine positions (not sorted)
    std::vector<uint32_t> not_mines;  // Other fields, not mines (not sorted)
    std::vector<bool> is_mine;  // True if index is a mine (sorted)

    Grid(uint16_t w, uint16_t h, uint32_t m);

    ~Grid();

    void Clear() override;

    private:

    void FindNeighbors();
};

#endif
