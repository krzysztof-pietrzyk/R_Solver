#ifndef Algorithm_hpp
#define Algorithm_hpp

#include "GridManager.hpp"

class Algorithm
{
    public:
    
    Algorithm(GridManager& grid_);

    ~Algorithm();

    virtual bool Run() = 0;

    protected:

    GridManager& grid;
};

#endif
