#ifndef GridGeneratorFromHash_hpp
#define GridGeneratorFromHash_hpp

#include "GridInternalGenerator.hpp"

class GridGeneratorFromHash : public GridInternalGenerator
{
    public:

    GridHash hash;
    
    GridGeneratorFromHash(GridSelfGenerated& grid);

    ~GridGeneratorFromHash();

    void Generate();
};

#endif
