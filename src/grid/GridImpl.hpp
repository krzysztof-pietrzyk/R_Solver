#ifndef GRID_IMPL_HPP
#define GRID_IMPL_HPP

#include "../utils/CachedVector.hpp"

#include "GridAccessPlayerIf.hpp"
#include "GridAccessGeneratorIf.hpp"
#include "GridAccessViewIf.hpp"
#include "GridDimensions.hpp"

#include <vector>
#include <cstdint>
#include <stdexcept>

class GridImpl : 
    public GridAccessPlayerIf,
    public GridAccessGeneratorIf,
    public GridAccessViewIf
{
    public:

    GridImpl(const GridDimensions dimensions);
    ~GridImpl();

    // GridAccessCommonIf
    virtual GridDimensions GetDimensions() const override;
    virtual uint16_t GetWidth() const override;
    virtual uint16_t GetHeight() const override;
    virtual uint32_t GetSize() const override;
    virtual uint32_t GetTotalMines() const override;
    virtual uint32_t GetTotalSafeFields() const override;
    virtual const std::vector<uint32_t>& GetNeighbors(uint32_t field) const override;

    // GridAccessPlayerIf
    virtual const CachedVector& GetVisibleFields() const override;
    virtual const CachedVector& GetFlaggedFields() const override;
    virtual uint8_t GetFieldValue(uint32_t field) const override;
    virtual bool IsLost() const override;
    virtual bool IsWon() const override;
    virtual void GiveUp() override;

    // GridAccessGeneratorIf
    virtual void SetMineFields(const CachedVector& new_mine_fields) override;
    virtual void SetFlaggedFields(const CachedVector& new_flagged_fields) override;
    virtual void SetVisibleFields(const CachedVector& new_visible_fields) override;
    virtual void SetFieldValues(const std::vector<uint8_t>& new_field_values) override;
    virtual void Reset() override;

    // GridAccessViewIf
    virtual const std::vector<FieldType>& GetFieldTypesToDisplay() override;

    protected:

    const GridDimensions dimensions;
    CachedVector mine_fields;
    CachedVector flagged_fields;
    CachedVector visible_fields;
    std::vector<uint8_t> field_values;
    std::vector<std::vector<uint32_t>> neighbors;
    bool is_lost;

    private:

    std::vector<FieldType> field_types_to_display;

    void FindNeighborsOfAllFields();
    FieldType GetFieldType(uint32_t field);
    FieldType GetFieldTypeLostGrid(uint32_t field);
    FieldType GetFieldTypeOngoingGrid(uint32_t field);
    FieldType GetFieldTypeNumbered(uint32_t field);
};

#endif
