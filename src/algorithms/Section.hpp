#ifndef Section_hpp
#define Section_hpp

#include <vector>
#include <algorithm>

#define MAX_SECTION_LEN 8
#define MAX_SECTION_NEIGHBORS 20

class Section
{
    public:

    Section();

    ~Section();

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
