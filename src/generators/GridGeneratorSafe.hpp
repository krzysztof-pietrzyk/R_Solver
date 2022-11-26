#ifndef GRID_GENERATOR_SAFE_HPP
#define GRID_GENERATOR_SAFE_HPP

#include "GridGeneratorUnsafe.hpp"

class GridGeneratorSafe : public GridGeneratorUnsafe
{
    public:

    GridGeneratorSafe(GridSelfGenerated& grid);

    ~GridGeneratorSafe();

    void SetStartingField(uint32_t starting_field);

    protected:

    void PrepareSafeFields() override;

    void CopySafeFields() override;
};

#endif
