#ifndef GridManager_hpp
#define GridManager_hpp

#include <stdexcept>

#include "utils/BitMask.hpp"
#include "utils/Buffer.hpp"
#include "utils/Buffer2D.hpp"

class GridManager
{
    public:

    const unsigned short int W;  // Width
    const unsigned short int H;  // Height
    const unsigned int S;  // Size (Width * Height)
    const unsigned int M;  // Number of mines

    Buffer visible_fields;  // Positions of visible fields (not sorted)
	BitMask is_visible;  // True if index is visible (sorted)

    Buffer flags;  // Positions of flags (not sorted). Only for the purpose of clearing is_flag array quicker
    BitMask is_flag;  // True if index is a flag (sorted)

    Buffer2D neighbors;  // Buffer with positions of neighbors for each field (sorted)

    unsigned int left_click_counter;
    unsigned int right_click_counter;
    bool is_lost;

    GridManager(unsigned short int w, unsigned short int h, unsigned int m);

    ~GridManager();

    unsigned char FieldValue(unsigned int field);

    virtual void LeftClick(unsigned int field) = 0;

    virtual void RightClick(unsigned int field) = 0;

    //virtual void ShowUncovered() = 0;

    protected:

    void Clear();

    Buffer field_values;  // Values of all fields (sorted)

};

#endif
