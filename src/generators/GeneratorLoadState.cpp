// implemented header
#include "GeneratorLoadState.hpp"

// project includes

// std includes


GeneratorLoadState::GeneratorLoadState(GridGeneratorIf& grid_)
    : GeneratorExternal(grid_)
{
    LOGGER(LogLevel::INIT) << "GeneratorLoadState";
}

GeneratorLoadState::~GeneratorLoadState()
{

}

void GeneratorLoadState::LoadGridStateFromSource()
{
    generated_mine_fields = loading_source->GetMines();
    LOGGER_ASSERT(!(generated_mine_fields == GridState::unspecified_layer), 
        "GeneratorLoadState::LoadGridStateFromSource - No mines were provided");
    generated_visible_fields = loading_source->GetVisible();
    generated_flagged_fields = loading_source->GetFlagged();
    generated_lost = loading_source->GetIsLost();
    CalculateFieldValues();
}
