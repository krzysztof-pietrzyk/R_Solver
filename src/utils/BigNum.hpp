#ifndef BIG_NUM_HPP
#define BIG_NUM_HPP

#include "Logger.hpp"

#include <iomanip>
#include <bitset>
#include <cmath>

class BigNum
{
    /*
    This class handles SOME math operations for very large and very small POSITIVE numbers.
    It DOES NOT support subtraction.
    It DOES NOT support negative numbers.
    */
    public:

    BigNum();
    ~BigNum();

    BigNum(const BigNum& other);
    BigNum(const uint64_t& value);

    std::string StrBits() const;
    std::string StrBase2() const;
    std::string StrBase10() const;

    void operator= (const BigNum& other);
    void operator= (const uint64_t& other);

    BigNum operator+ (const BigNum& other) const;
    BigNum operator* (const BigNum& other) const;
    BigNum operator/ (const BigNum& other) const;

    void   operator+=(const BigNum& other);
    void   operator*=(const BigNum& other);
    void   operator/=(const BigNum& other);

    BigNum operator+ (const uint64_t& other) const;
    BigNum operator* (const uint64_t& other) const;
    BigNum operator/ (const uint64_t& other) const;

    void   operator+=(const uint64_t& other);
    void   operator*=(const uint64_t& other);
    void   operator/=(const uint64_t& other);

    bool   operator> (const BigNum& other) const;
    bool   operator>=(const BigNum& other) const;
    bool   operator< (const BigNum& other) const;
    bool   operator<=(const BigNum& other) const;
    bool   operator==(const BigNum& other) const;
    bool   operator!=(const BigNum& other) const;

    protected:

    double base;
    int64_t exponent;

    static const uint64_t exponent_mask;
    static const uint64_t mantissa_mask;
	static const uint64_t is_negative_mask;
    static const uint64_t hidden_mantissa_bit;
    static const uint64_t overflow_bit;
    static const uint64_t exponent_value_shifted;
	static const uint64_t exponent_value_shift;
    static const unsigned exponent_bit_shift;
    static const double log2_10;

    inline void Normalize();

    inline double ShiftAndAdd(const double value_small, const double value_large, const uint32_t shift, bool& overflow) const;
};

#endif
