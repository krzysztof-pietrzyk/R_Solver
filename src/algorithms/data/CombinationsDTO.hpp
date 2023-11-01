#ifndef COMBINATIONS_DTO_HPP
#define COMBINATIONS_DTO_HPP

// project includes
#include "../../utils/BigNum.hpp"

// std includes
#include <vector>

// forward declarations
struct GridDimensions;


struct CombinationsDTO
{
    std::vector<BigNum> field_combinations;
    // number of combinations in which one remaining field is a mine (the same number for each remaining field)
    BigNum remaining_fields_combinations;
    BigNum total_combinations;

    CombinationsDTO(GridDimensions dim);
};

#endif
