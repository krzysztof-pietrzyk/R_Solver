#ifndef GRID_INTERNAL_IMPL_HPP
#define GRID_INTERNAL_IMPL_HPP

#include "GridImpl.hpp"

class GridInternalImpl : public GridImpl
{
    public:

    GridInternalImpl(GridDimensions dimensions);
    ~GridInternalImpl();

    // GridAccessPlayerIf
    virtual PlayerActionResult SetVisible(uint32_t field) override;
    virtual PlayerActionResult SetFlag(uint32_t field) override;

    private:

    CachedVector chain_reaction_zeros;

    void StartChainReactionAt(uint32_t field);
    void HandleChainReactionAt(uint32_t field);
};

#endif
