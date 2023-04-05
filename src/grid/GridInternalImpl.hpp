#ifndef GRID_INTERNAL_IMPL_HPP
#define GRID_INTERNAL_IMPL_HPP

#include "GridImpl.hpp"

class GridInternalImpl : public GridImpl
{
    public:

    // GridAccessPlayerIf
    virtual void SetVisible(uint32_t field) override;
    virtual void SetFlag(uint32_t field) override;
};

#endif
