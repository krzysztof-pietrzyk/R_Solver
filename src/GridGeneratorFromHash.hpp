#ifndef GridGeneratorFromHash_hpp
#define GridGeneratorFromHash_hpp

#include <cstring>

#include "GridGenerator.hpp"

class GridGeneratorFromHash : public GridGenerator
{
    public:

    char* hash;
    const unsigned int hash_length;
    
    GridGeneratorFromHash(Grid& grid);

    ~GridGeneratorFromHash();

    void Generate();

    void SetHash(char*);
};

#endif
