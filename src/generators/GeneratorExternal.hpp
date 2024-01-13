#ifndef GENERATOR_EXTERNAL_HPP
#define GENERATOR_EXTERNAL_HPP

// project includes
#include "Generator.hpp"
#include "../grid/state/GridState.hpp"
#include "../utils/Logger.hpp"

// std includes

// forward declarations


class GeneratorExternal : public Generator
{
    public:

    GeneratorExternal(GridGeneratorIf& grid_);

    ~GeneratorExternal();

    virtual void GenerateGrid() override final;

    void SetLoadingSource(GridState* new_loading_source);

    protected:

    GridState* loading_source;

    virtual void LoadGridStateFromSource() = 0;
};

#endif
