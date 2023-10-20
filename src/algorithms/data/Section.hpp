#ifndef SECTION_HPP
#define SECTION_HPP

#include <vector>
#include <algorithm>
#include <cstdint>

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

    uint32_t origin;
    std::vector<uint32_t> fields;
    size_t fields_index;
    std::vector<uint32_t> neighbors;
    size_t neighbors_index;
    uint8_t value;

    void AddField(const uint32_t field);

    void AddNeighbor(const uint32_t field);

    bool HasNeighbor(const uint32_t field) const;

    void Clear();
};

#endif
