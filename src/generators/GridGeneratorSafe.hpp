#ifndef GridGeneratorSafe_hpp
#define GridGeneratorSafe_hpp

#include "GridGeneratorUnsafe.hpp"

class GridGeneratorSafe : public GridGeneratorUnsafe
{
    public:

    GridGeneratorSafe(GridSelfGenerated& grid);

    ~GridGeneratorSafe();

    void SetStartingField(unsigned int starting_field);

    protected:

    void PrepareSafeFields();

    void CopySafeFields();
};

#endif
