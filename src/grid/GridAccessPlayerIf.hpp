#ifndef GRID_ACCESS_PLAYER_IF_HPP
#define GRID_ACCESS_PLAYER_IF_HPP

#include "GridAccessCommonIf.hpp"

class GridAccessPlayerIf : public GridAccessCommonIf
{
    public:

    virtual const CachedVector& GetVisibleFields() const = 0;
    virtual const CachedVector& GetFlaggedFields() const = 0;
    virtual const std::vector<uint32_t>& GetFieldNeighbors(uint32_t field) = 0;
    virtual uint8_t GetFieldValue(uint32_t field) = 0;

    virtual void SetVisible(uint32_t field) = 0;
    virtual void SetFlag(uint32_t field) = 0;
    virtual bool IsLost() = 0;
    virtual bool IsWon() = 0;
};

#endif
