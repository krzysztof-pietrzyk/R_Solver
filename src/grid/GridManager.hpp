#ifndef GridManager_hpp
#define GridManager_hpp

#include <vector>
#include <stdexcept>

#define for_neighbors_of(f) const unsigned int z__=f*GridManager::MAX_NEIGHBORS;const unsigned int c__=z__+neighbors_l[f];for(size_t x=z__;x<c__;x++)
#define for_grid_neighbors_of(f) const unsigned int z__=f*GridManager::MAX_NEIGHBORS;const unsigned int c__=z__+grid.neighbors_l[f];for(size_t x=z__;x<c__;x++)

class GridManager
{
    public:

    const unsigned short int W;  // Width
    const unsigned short int H;  // Height
    const unsigned int S;  // Size (Width * Height)
    const unsigned int M;  // Number of mines
    const unsigned int NM;  // Number of fields that are not mines (S - M)
    static const unsigned int MAX_NEIGHBORS = 8;

    std::vector<unsigned int> visible_fields;  // Positions of visible fields (not sorted)
    unsigned int visible_fields_index;  // Current count of visible fields
	std::vector<bool> is_visible;  // True if index is visible (sorted)

    std::vector<unsigned int> flags;  // Positions of flags (not sorted). Only for the purpose of clearing is_flag array quicker
    unsigned int flags_index;  // Current count of flags
    std::vector<bool> is_flag;  // True if index is a flag (sorted)

    std::vector<unsigned int> neighbors;
    std::vector<unsigned char> neighbors_l;

    unsigned int left_click_counter;
    unsigned int right_click_counter;
    bool is_lost;

    GridManager(unsigned short int w, unsigned short int h, unsigned int m);

    ~GridManager();

    unsigned char FieldValue(unsigned int field);

    virtual void LeftClick(unsigned int field) = 0;

    virtual void RightClick(unsigned int field) = 0;

    // virtual void PrintUncovered() = 0;

    protected:

    void Clear();

    std::vector<unsigned char> field_values;  // Values of all fields (sorted)

};

#endif
