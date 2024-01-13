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
    virtual GridState GetState() const override;

    // GridAlgorithmIf
    virtual PlayerActionResult SetVisible(uint32_t field) override;
    virtual PlayerActionResult SetFlag(uint32_t field) override;
    virtual void GiveUp() override;

    // GridGeneratorIf
    virtual void SetMineFields(const CachedVector& new_mine_fields) override;

    // GridViewIf
    virtual const std::vector<FieldType>& GetFieldTypesToDisplay() override;

    private:

    CachedVector mine_fields;
    CachedVector chain_reaction_zeros;

    std::vector<FieldType> field_types_to_display;

    void StartChainReactionAt(uint32_t field);
    void HandleChainReactionAt(uint32_t field);

    FieldType GetFieldType(uint32_t field);
    FieldType GetFieldTypeLostGrid(uint32_t field);
    FieldType GetFieldTypeOngoingGrid(uint32_t field);
    FieldType GetFieldTypeNumbered(uint32_t field);
};

#endif
