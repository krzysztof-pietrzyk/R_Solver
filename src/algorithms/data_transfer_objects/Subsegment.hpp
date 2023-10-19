#ifndef SUBSEGMENT_HPP
#define SUBSEGMENT_HPP

#include <vector>
#include <map>
#include <cstdint>

struct Subsegment
{
    std::vector<uint32_t> fields;
    std::vector<uint8_t> possible_values;
    std::map<uint8_t, uint32_t> combinations_for_value;
    size_t total_possibilities;
    size_t current_possibility_id;
};

#endif
