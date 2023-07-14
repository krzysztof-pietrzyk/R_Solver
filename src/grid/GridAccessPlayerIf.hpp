#ifndef GRID_ACCESS_PLAYER_IF_HPP
#define GRID_ACCESS_PLAYER_IF_HPP

#include "../utils/CachedVector.hpp"
#include "GridAccessCommonIf.hpp"

enum PlayerActionResult
{
    CORRECT,
    INCORRECT
};

class GridAccessPlayerIf : public GridAccessCommonIf
{
    public:

    virtual const CachedVector& GetVisibleFields() const = 0;
    virtual const CachedVector& GetFlaggedFields() const = 0;
    virtual uint8_t GetFieldValue(uint32_t field) const = 0;

    virtual PlayerActionResult SetVisible(uint32_t field) = 0;
    virtual PlayerActionResult SetFlag(uint32_t field) = 0;
    virtual bool IsLost() const = 0;
    virtual bool IsWon() const = 0;
    virtual void GiveUp() = 0;
};

#endif
