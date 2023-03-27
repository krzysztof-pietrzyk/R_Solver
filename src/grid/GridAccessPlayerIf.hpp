#ifndef GRID_ACCESS_PLAYER_IF_HPP
#define GRID_ACCESS_PLAYER_IF_HPP

#include "GridAccessReadIf.hpp"

class GridAccessPlayerIf : public GridAccessReadIf
{
    public:

    virtual void SetVisible(uint32_t field) = 0;
    virtual void SetFlag(uint32_t field) = 0;
    virtual bool IsLost() = 0;
    virtual bool IsWon() = 0;
};

#endif
