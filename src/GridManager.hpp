#ifndef GridManager_hpp
#define GridManager_hpp

#include "Grid.hpp"
#include "GridGeneratorFactory.hpp"
#include "GridViewFactory.hpp"

class GridManager : public Grid
{
    public:

    unsigned int* face;
    unsigned int face_index;
    bool* is_face;

    unsigned int* border;
    unsigned int border_index;
    bool* is_border;

    unsigned int left_click_counter;
    unsigned int right_click_counter;
    bool is_lost;

    GridManager(unsigned short int w, unsigned short int h, unsigned int m);

    ~GridManager();

    void Generate();

    void Display();

    void RefreshFace();

    void RefreshBorder();

    void LeftClick(unsigned int field);

    void RightClick(unsigned int field);

    private:

    unsigned int* face_internal_0;
    unsigned int* face_internal_1;
    unsigned int* border_internal_0;
    unsigned int* border_internal_1;
    bool face_internal_indicator;
    bool border_internal_indicator;
    unsigned int last_read_index_face;
    unsigned int last_read_index_border;

    GridGenerator* generator;
    GridView* view;

    void Clear();
};

#endif
