#ifndef GridGeneratorFromHash_hpp
#define GridGeneratorFromHash_hpp

#include <cstring>

#include "GridInternalGenerator.hpp"

class GridGeneratorFromHash : public GridInternalGenerator
{
    public:

    char* hash;
    const unsigned int hash_length;
    
    GridGeneratorFromHash(GridSelfGenerated& grid);

    ~GridGeneratorFromHash();

    void Generate();

    void SetHash(char*);
};

#endif
