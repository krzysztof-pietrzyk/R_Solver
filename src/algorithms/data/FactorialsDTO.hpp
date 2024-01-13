#ifndef FACTORIALS_DTO_HPP
#define FACTORIALS_DTO_HPP

// project includes

// std includes
#include <cstdint>
#include <vector>

// forward declarations
struct GridDimensions;
class BigNum;


struct FactorialsDTO
{
    std::vector<BigNum> factorial;
    std::vector<BigNum> factorial_reciprocal;

    FactorialsDTO(GridDimensions dim);
};

#endif
