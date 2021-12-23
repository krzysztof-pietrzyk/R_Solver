#ifndef GridManager_hpp
#define GridManager_hpp

class GridManager
{
    public:

    unsigned short int W;  // Width
    unsigned short int H;  // Height
    unsigned int S;  // Size (Width * Height)
    unsigned int M;  // Number of mines

    unsigned int* visible_fields;  // Positions of visible fields (not sorted)
    unsigned int visible_fields_index;  // Current count of visible fields
	bool* is_visible;  // True if index is visible (sorted)

    unsigned int* flags;  // Positions of flags (not sorted). Only for the purpose of clearing is_flag array quicker
    unsigned int flags_index;  // Current count of flags
    bool* is_flag;  // True if index is a flag (sorted)

    unsigned int** neighbors;  // Array of pointers to positions of neighbors for each field (sorted)
    unsigned char* neighbors_l;  // Number of neighbors of each field (sorted)

    unsigned int left_click_counter;
    unsigned int right_click_counter;
    bool is_lost;

    GridManager();

    ~GridManager();

    virtual void LeftClick(unsigned int field) = 0;

    virtual void RightClick(unsigned int field) = 0;

    protected:

    void Clear();

    /* TODO: this should be protected */ public: unsigned char* field_values;  // Values of all fields (sorted)

};

#endif
