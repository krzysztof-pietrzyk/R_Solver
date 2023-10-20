#ifndef FACTORIALS_DTO_HPP
#define FACTORIALS_DTO_HPP

#include <vector>
#include <cstdint>

#include "../../grid/GridDimensions.hpp"
#include "../../utils/BigNum.hpp"

struct FactorialsDTO
{
    std::vector<BigNum> factorial;
    std::vector<BigNum> factorial_reciprocal;

    FactorialsDTO(GridDimensions dim);
};

#endif
