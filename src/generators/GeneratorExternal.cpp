// implemented header
#include "GeneratorExternal.hpp"

// project includes

// std includes


GeneratorExternal::GeneratorExternal(GridGeneratorIf& grid_)
    : Generator(grid_)
{
    LOGGER(LogLevel::INIT) << "GeneratorExternal";
    loading_source = nullptr;  // Must be assigned before usage
}

GeneratorExternal::~GeneratorExternal()
{

}

void GeneratorExternal::GenerateGrid()
{
    LOGGER(LogLevel::DEBUG4) << "GeneratorExternal::GenerateGrid";
    ClearGeneratedVectors();
    LOGGER_ASSERT(loading_source != nullptr, "GeneratorExternal::GenerateGrid - loading_source is nullptr");
    LoadGridStateFromSource();  // Pure virtual
    CopyGeneratedDataToGrid();
}

void GeneratorExternal::SetLoadingSource(GridState* new_loading_source)
{
    loading_source = new_loading_source;
}
