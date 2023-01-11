#ifndef GRID_MANAGER_HPP
#define GRID_MANAGER_HPP

#include "../statistics/StatisticsProducer.hpp"

#include <vector>
#include <stdexcept>
#include <cstdint>

//#define DEBUG_MODE_PRINT

class GridManager : public StatisticsProducer
{
    public:

    const uint16_t W;  // Width
    const uint16_t H;  // Height
    const uint32_t S;  // Size (Width * Height)
    const uint32_t M;  // Number of mines
    const uint32_t NM;  // Number of fields that are not mines (S - M)

    std::vector<uint32_t> visible_fields;  // Positions of visible fields (not sorted)
    uint32_t visible_fields_index;  // Current count of visible fields
	std::vector<bool> is_visible;  // True if index is visible (sorted)

    std::vector<uint32_t> flags;  // Positions of flags (not sorted). Only for the purpose of clearing is_flag array quicker
    uint32_t flags_index;  // Current count of flags
    std::vector<bool> is_flag;  // True if index is a flag (sorted)

    std::vector<std::vector<uint32_t>> neighbors;

    uint32_t left_click_counter;
    uint32_t right_click_counter;
    bool is_lost;

    GridManager(uint16_t w, uint16_t h, uint32_t m);

    ~GridManager();

    uint8_t FieldValue(uint32_t field);

    virtual bool LeftClick(uint32_t field) = 0;

    virtual bool RightClick(uint32_t field) = 0;

    #ifdef DEBUG_MODE_PRINT
    virtual void PrintUncovered() const = 0;
    #endif

    protected:

    virtual void Clear();

    std::vector<uint8_t> field_values;  // Values of all fields (sorted)

    virtual bool CheckVisible(uint32_t field);

};

#endif
