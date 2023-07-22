#ifndef GRID_INTERNAL_HPP
#define GRID_INTERNAL_HPP

#include "GridImpl.hpp"

class GridInternal : public GridImpl
{
    public:

    GridInternal(GridDimensions dimensions);
    ~GridInternal();

    // GridAccessPlayerIf
    virtual PlayerActionResult SetVisible(uint32_t field) override;
    virtual PlayerActionResult SetFlag(uint32_t field) override;

    private:

    CachedVector chain_reaction_zeros;

    void StartChainReactionAt(uint32_t field);
    void HandleChainReactionAt(uint32_t field);
};

#endif
