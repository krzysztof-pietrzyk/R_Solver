// implemented header
#include "FactorialsDTO.hpp"

// project includes
#include "../../grid/GridDimensions.hpp"
#include "../../utils/BigNum.hpp"

// std includes


FactorialsDTO::FactorialsDTO(GridDimensions dim)
{
    factorial = std::vector<BigNum>(dim.size, BigNum(0));
    factorial_reciprocal = std::vector<BigNum>(dim.size, BigNum(0));

    BigNum current_factorial = BigNum(1);
    BigNum current_factorial_reciprocal = BigNum(1);
    factorial[0] = current_factorial;
    factorial_reciprocal[0] = current_factorial_reciprocal;
    for(uint32_t i = 1; i < dim.size; i++)
    {
        current_factorial *= i;
        current_factorial_reciprocal /= i;
        factorial[i] = current_factorial;
        factorial_reciprocal[i] = current_factorial_reciprocal;
    }
}
