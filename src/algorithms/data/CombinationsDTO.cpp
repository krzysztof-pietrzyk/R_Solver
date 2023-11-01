// implemented header
#include "CombinationsDTO.hpp"

// project includes
#include "../../grid/GridDimensions.hpp"

// std includes


CombinationsDTO::CombinationsDTO(GridDimensions dim)
{
    field_combinations = std::vector<BigNum>(dim.size, BigNum(0));
    total_combinations = BigNum(0);
    remaining_fields_combinations = BigNum(0);
}
