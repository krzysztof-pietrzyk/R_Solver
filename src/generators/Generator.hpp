#ifndef GENERATOR_HPP
#define GENERATOR_HPP

// project includes
#include "../grid/GridGeneratorIf.hpp"
#include "../statistics/StatisticsProducer.hpp"
#include "../utils/CachedVector.hpp"

// std includes

// forward declarations


class Generator : public StatisticsProducer
{
    public:

    Generator(GridGeneratorIf& grid_);

    ~Generator();

    virtual void GenerateGrid() = 0;

    protected:

    GridGeneratorIf& grid;
    const GridDimensions grid_dim;
    static const uint8_t value_for_mine_fields;

    CachedVector generated_mine_fields;
    std::vector<uint8_t> generated_field_values;
    CachedVector generated_visible_fields;
    CachedVector generated_flagged_fields;
    bool generated_lost;

    uint8_t CalculateFieldValue(uint32_t field);

    void CalculateFieldValues();

    void CopyGeneratedDataToGrid();

    void ClearGeneratedVectors();
};

#endif
