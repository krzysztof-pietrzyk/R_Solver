#ifndef GRID_VIEW_IF_HPP
#define GRID_VIEW_IF_HPP

#include "GridCommonIf.hpp"
#include "FieldType.hpp"

#include <vector>

class GridViewIf : public GridCommonIf
{
    public:

    virtual const std::vector<FieldType>& GetFieldTypesToDisplay() = 0;
};

#endif
