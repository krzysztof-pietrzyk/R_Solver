#ifndef GRID_GENERATOR_FROM_HASH_HPP
#define GRID_GENERATOR_FROM_HASH_HPP

#include "GridInternalGenerator.hpp"

class GridGeneratorFromHash : public GridInternalGenerator
{
    public:

    GridHash hash;
    
    GridGeneratorFromHash(GridSelfGenerated& grid);

    ~GridGeneratorFromHash();

    void Generate() override;
};

#endif
