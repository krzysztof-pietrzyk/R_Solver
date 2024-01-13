#ifndef SECTION_HPP
#define SECTION_HPP

// project includes

// std includes
#include <cstdint>
#include <vector>

// forward declarations


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

    private:

    static const uint32_t max_section_length;
    static const uint32_t max_section_neighbors;
};

#endif
