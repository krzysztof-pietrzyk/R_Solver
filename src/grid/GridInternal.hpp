#ifndef GRID_INTERNAL_HPP
#define GRID_INTERNAL_HPP

// project includes
#include "Grid.hpp"

// std includes

// forward declarations


class GridInternal : public Grid
{
    public:

    GridInternal(GridDimensions dimensions);
    ~GridInternal();

    // GridCommonIf
    virtual GridHash GetHash() const override;

    // GridAlgorithmIf
    virtual PlayerActionResult SetVisible(uint32_t field) override;
    virtual PlayerActionResult SetFlag(uint32_t field) override;
    virtual void GiveUp() override;

    private:

    CachedVector chain_reaction_zeros;

    void StartChainReactionAt(uint32_t field);
    void HandleChainReactionAt(uint32_t field);
};

#endif
