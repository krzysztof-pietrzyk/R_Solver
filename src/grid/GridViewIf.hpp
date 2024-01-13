#ifndef GRID_VIEW_IF_HPP
#define GRID_VIEW_IF_HPP

// project includes
#include "FieldType.hpp"
#include "GridCommonIf.hpp"

// std includes

// forward declarations


class GridViewIf : public GridCommonIf
{
    public:

    virtual const std::vector<FieldType>& GetFieldTypesToDisplay() = 0;
};

#endif
