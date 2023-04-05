#ifndef GRID_ACCESS_VIEW_IF_HPP
#define GRID_ACCESS_VIEW_IF_HPP

#include "GridAccessCommonIf.hpp"
#include "FieldType.hpp"

#include <vector>

class GridAccessViewIf : public GridAccessCommonIf
{
    public:

    virtual const std::vector<FieldType>& GetFieldTypesToDisplay() = 0;
};

#endif
