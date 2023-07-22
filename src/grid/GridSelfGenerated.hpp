#ifndef GRID_SELF_GENERATED_HPP
#define GRID_SELF_GENERATED_HPP

#include "Grid.hpp"
#include "GridHash.hpp"
#include "../statistics/collectors/StatisticsCollectorFieldTypes.hpp"

class GridSelfGenerated : public Grid
{
    public:

    GridHash hash;

    GridSelfGenerated(uint16_t w, uint16_t h, uint32_t m);

    ~GridSelfGenerated();

    bool LeftClick(uint32_t field) override;

    bool RightClick(uint32_t field) override;

    void CalculateHash();

    void CalculateValues();

    #ifdef DEBUG_MODE_PRINT
    virtual void PrintUncovered() const override;
    #endif

    protected:

    std::vector<uint32_t> zcr_zeros;  // Temporary array used in ZeroChainReaction
    uint32_t zcr_zeros_index;  // Temporary index used in ZeroChainReaction
    std::vector<bool> zcr_is_zero;  // Temporary array used in ZeroChainReaction

    StatisticsCollectorFieldTypes* statistics_field_types;

    void ZeroChainReaction(uint32_t field);

    void ClearZCR();
};

#endif
