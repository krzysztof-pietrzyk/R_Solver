#ifndef BigNum_hpp
#define BigNum_hpp

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
    BigNum(const unsigned long long& value);

    std::string StrBits() const;
    std::string StrBase2() const;
    std::string StrBase10() const;

    void operator= (const BigNum& other);
    void operator= (const unsigned long long& other);

    BigNum operator+ (const BigNum& other) const;
    BigNum operator* (const BigNum& other) const;
    BigNum operator/ (const BigNum& other) const;

    void   operator+=(const BigNum& other);
    void   operator*=(const BigNum& other);
    void   operator/=(const BigNum& other);

    BigNum operator+ (const unsigned long long& other) const;
    BigNum operator* (const unsigned long long& other) const;
    BigNum operator/ (const unsigned long long& other) const;

    void   operator+=(const unsigned long long& other);
    void   operator*=(const unsigned long long& other);
    void   operator/=(const unsigned long long& other);

    bool   operator> (const BigNum& other) const;
    bool   operator>=(const BigNum& other) const;
    bool   operator< (const BigNum& other) const;
    bool   operator<=(const BigNum& other) const;
    bool   operator==(const BigNum& other) const;
    bool   operator!=(const BigNum& other) const;

    protected:

    double base;
    long long exponent;

    static const unsigned long long exponent_mask;
    static const unsigned long long mantissa_mask;
	static const unsigned long long is_negative_mask;
    static const unsigned long long hidden_mantissa_bit;
    static const unsigned long long overflow_bit;
    static const unsigned long long exponent_value_shifted;
	static const unsigned long long exponent_value_shift;
    static const unsigned exponent_bit_shift;
    static const double log2_10;

    inline void Normalize();

    inline double ShiftAndAdd(const double value_small, const double value_large, const unsigned int shift, bool& overflow) const;
};

#endif
