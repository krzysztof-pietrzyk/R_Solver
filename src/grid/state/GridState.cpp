// implemented header
#include "GridState.hpp"

// project includes
#include "../../utils/Logger.hpp"

// std includes
#include <algorithm>
#include <iomanip>


const size_t GridState::expected_num_of_separators = 4;
const CachedVector GridState::unspecified_layer = CachedVector(0);
const GridHash GridState::unspecified_layer_hash = GridHash(CachedVector(0));
const char GridState::separator_symbol = '|';
const char GridState::lost_symbol = '1';
const char GridState::not_lost_symbol = '0';

GridState::GridState()
{
    hash_mines = GridHash();
    hash_flagged = GridHash();
    hash_visible = GridHash();
    grid_size = 0;
    is_lost = false;
}

GridState::GridState(const CachedVector& mines)
{
    hash_mines = GridHash(mines);
    hash_flagged = unspecified_layer_hash;
    hash_visible = unspecified_layer_hash;
    grid_size = mines.MaxSize();
    is_lost = false;
}

GridState::GridState(const CachedVector& mines, const CachedVector& flagged, const CachedVector& visible)
{
    hash_mines = GridHash(mines);
    hash_flagged = GridHash(flagged);
    hash_visible = GridHash(visible);
    grid_size = mines.MaxSize();
    is_lost = false;
    for(uint32_t i = 0; i < grid_size; i++)
    {
        if(mines.Contains(i) && visible.Contains(i))
        {
            is_lost = true;
        }
    }
}

GridState::GridState(const std::string& state)
{
    std::string state_string = std::string(state);
    size_t num_of_separators = std::count(state_string.begin(), state_string.end(), '|');
    LOGGER_ASSERT(num_of_separators == expected_num_of_separators, "GridState(const std::string&) - Bad separators");
    std::replace(state_string.begin(), state_string.end(), '|', ' ');
    std::stringstream ss(state_string);
    std::string temp;
    try
    {
        ss >> temp;
        grid_size = std::stoi(temp);
        ss >> temp;
        SetIsLost(temp.at(0));
        ss >> temp;
        hash_mines = (temp == "" ? unspecified_layer_hash : GridHash(temp, grid_size));
        ss >> temp;
        hash_flagged = (temp == "" ? unspecified_layer_hash : GridHash(temp, grid_size));
        ss >> temp;
        hash_visible = (temp == "" ? unspecified_layer_hash : GridHash(temp, grid_size));
    }
    catch(const std::exception&)
    {
        LOGGER_THROW("GridState(const std::string&) - Incompatible or corrupted state string");
    }
}

GridState::~GridState()
{

}

std::string GridState::String() const
{
    return std::to_string(grid_size) + separator_symbol + \
        GetIsLostSymbol() + separator_symbol + \
        hash_mines.String() + separator_symbol + \
        hash_flagged.String() + separator_symbol + \
        hash_visible.String();
}

CachedVector GridState::GetMines() const
{
    return (hash_mines == unspecified_layer_hash ? unspecified_layer : hash_mines.Unhash());
}

CachedVector GridState::GetFlagged() const
{
    return (hash_flagged == unspecified_layer_hash ? unspecified_layer : hash_flagged.Unhash());
}

CachedVector GridState::GetVisible() const
{
    return (hash_visible == unspecified_layer_hash ? unspecified_layer : hash_visible.Unhash());
}

bool GridState::GetIsLost() const
{
    return is_lost;
}

GridState& GridState::operator=(const GridState& other)
{
    grid_size = other.grid_size;
    hash_mines = other.hash_mines;
    hash_flagged = other.hash_flagged;
    hash_visible = other.hash_visible;
    return *this;
}

bool GridState::operator==(const GridState& other) const
{
    return String() == other.String();
}

char GridState::GetIsLostSymbol() const
{
    char result;
    if(is_lost)
    {
        result = lost_symbol;
    }
    else
    {
        result = not_lost_symbol;
    }
    return result;
}

void GridState::SetIsLost(char symbol)
{
    if(symbol == lost_symbol)
    {
        is_lost = true;
    }
    else if(symbol == not_lost_symbol)
    {
        is_lost = false;
    }
    else
    {
        LOGGER_THROW("GridState::SetIsLost - Wrong symbol: " + symbol);
    }
}
