#ifndef GRID_HPP
#define GRID_HPP

// project includes
#include "GridAlgorithmIf.hpp"
#include "GridGeneratorIf.hpp"
#include "GridViewIf.hpp"
#include "../utils/CachedVector.hpp"

// std includes

// forward declarations


class Grid : 
    public GridAlgorithmIf,
    public GridGeneratorIf,
    public GridViewIf
{
    public:

    Grid(GridDimensions dimensions);
    ~Grid();

    // GridCommonIf
    virtual GridDimensions GetDimensions() const override;
    virtual const std::vector<uint32_t>& GetNeighbors(uint32_t field) const override;
    virtual bool IsLost() const override;
    virtual bool IsWon() const override;

    // GridAlgorithmIf
    virtual const CachedVector& GetVisibleFields() const override;
    virtual const CachedVector& GetFlaggedFields() const override;
    virtual uint8_t GetFieldValue(uint32_t field) const override;

    // GridGeneratorIf
    virtual void SetFlaggedFields(const CachedVector& new_flagged_fields) override;
    virtual void SetVisibleFields(const CachedVector& new_visible_fields) override;
    virtual void SetFieldValues(const std::vector<uint8_t>& new_field_values) override;
    virtual void SetLost(bool new_is_lost) override;
    virtual void Reset() override;

    protected:

    const GridDimensions dimensions;
    CachedVector flagged_fields;
    CachedVector visible_fields;
    std::vector<uint8_t> field_values;
    std::vector<std::vector<uint32_t>> neighbors;
    bool is_lost;

    virtual bool CheckVisible(uint32_t field) const;

    private:

    void VerifyDimensions(GridDimensions dim) const;
    void FindNeighborsOfAllFields();
};

#endif
