#ifndef Section_hpp
#define Section_hpp

#include <vector>
#include <algorithm>

// Section may contain up to 8 fields, like so:
// 00 01 02
// 03 XX 04
// 05 06 07
#define MAX_SECTION_LEN 8

// Section may have up to 20 neighbors, like so:
// 00 01 02 03 04
// 05    06    07
// 08 09 XX 10 11
// 12    13    14
// 15 16 17 18 19
#define MAX_SECTION_NEIGHBORS 20

class Section
{
    public:

    Section();

    ~Section();

    unsigned int origin;
    std::vector<unsigned int> fields;
    size_t fields_index;
    std::vector<unsigned int> neighbors;
    size_t neighbors_index;
    unsigned char value;

    void AddField(const unsigned int field);

    void AddNeighbor(const unsigned int field);

    bool HasNeighbor(const unsigned int field) const;

    void Clear();
};

#endif
