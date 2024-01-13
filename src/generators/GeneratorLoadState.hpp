#ifndef GENERATOR_LOAD_STATE_HPP
#define GENERATOR_LOAD_STATE_HPP

// project includes
#include "GeneratorExternal.hpp"
#include "../grid/state/GridState.hpp"

// std includes

// forward declarations


class GeneratorLoadState : public GeneratorExternal
{
    public:

    GeneratorLoadState(GridGeneratorIf& grid_);

    ~GeneratorLoadState();

    protected:

    virtual void LoadGridStateFromSource() override;
};

#endif
