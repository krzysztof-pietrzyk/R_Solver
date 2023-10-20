#ifndef GRID_ALGORITHM_ANALYSIS_IF_HPP
#define GRID_ALGORITHM_ANALYSIS_IF_HPP

#include "../utils/CachedVector.hpp"

#include "GridCommonIf.hpp"

class GridAlgorithmAnalysisIf : public GridCommonIf
{
    public:

    virtual const CachedVector& GetVisibleFields() const = 0;
    virtual const CachedVector& GetFlaggedFields() const = 0;
    virtual uint8_t GetFieldValue(uint32_t field) const = 0;
    virtual bool IsLost() const = 0;
    virtual bool IsWon() const = 0;
};

#endif
