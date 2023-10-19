#ifndef COMBINATIONS_DTO_HPP
#define COMBINATIONS_DTO_HPP

#include <vector>
#include <cstdint>

#include "../../grid/GridDimensions.hpp"
#include "../../utils/BigNum.hpp"

struct CombinationsDTO
{
    std::vector<BigNum> field_combinations;
    // number of combinations in which one remaining field is a mine (the same number for each remaining field)
    BigNum remaining_fields_combinations;
    BigNum total_combinations;

    CombinationsDTO(GridDimensions dim);
};

#endif
