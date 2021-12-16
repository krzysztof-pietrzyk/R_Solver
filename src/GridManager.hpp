#ifndef GridManager_hpp
#define GridManager_hpp

#include "Grid.hpp"
#include "GridGeneratorFactory.hpp"
#include "GridViewFactory.hpp"

class GridManager : public Grid
{
    public:

    unsigned int left_click_counter;
    unsigned int right_click_counter;
    bool is_lost;

    GridManager(unsigned short int w, unsigned short int h, unsigned int m);

    ~GridManager();

    void Generate();

    void Display();

    void LeftClick(unsigned int field);

    void RightClick(unsigned int field);

    private:

    GridGenerator* generator;
    GridView* view;

    void Clear();
};

#endif
