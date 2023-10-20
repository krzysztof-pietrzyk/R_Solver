#ifndef GRID_INTERNAL_HPP
#define GRID_INTERNAL_HPP

#include "Grid.hpp"

class GridInternal : public Grid
{
    public:

    GridInternal(GridDimensions dimensions);
    ~GridInternal();

    // GridCommonIf
    virtual GridHash GetHash() const override;

    // GridAlgorithmActionIf
    virtual PlayerActionResult SetVisible(uint32_t field) override;
    virtual PlayerActionResult SetFlag(uint32_t field) override;
    virtual bool IsLost() const override;
    virtual bool IsWon() const override;
    virtual void GiveUp() override;

    private:

    CachedVector chain_reaction_zeros;

    void StartChainReactionAt(uint32_t field);
    void HandleChainReactionAt(uint32_t field);
};

#endif
