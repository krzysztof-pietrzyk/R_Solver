#include "BigNum.hpp"

const unsigned long long BigNum::exponent_mask          = 0x7FF0000000000000ULL;
const unsigned long long BigNum::mantissa_mask          = 0x000FFFFFFFFFFFFFULL;
const unsigned long long BigNum::is_negative_mask       = 0x8000000000000000ULL;
const unsigned long long BigNum::hidden_mantissa_bit    = 0x0010000000000000ULL;
const unsigned long long BigNum::overflow_bit           = 0x0020000000000000ULL;
const unsigned long long BigNum::exponent_value_shift   = 1023ULL;
const unsigned BigNum::exponent_bit_shift               = 52U;
const unsigned long long BigNum::exponent_value_shifted = BigNum::exponent_value_shift << BigNum::exponent_bit_shift;
const double BigNum::log2_10                            = 3.3219280948873623479;

BigNum::BigNum()                                { exponent = 0LL; base = 0.0; }
BigNum::BigNum(const BigNum& other)             { *this = other; }
BigNum::BigNum(const unsigned long long& value) { *this = value; }

BigNum::~BigNum() {}

void BigNum::Normalize()
{
    if(base == 0.0) { return; }
    // convert base (double) into its bit representation (unsigned long long)
    unsigned long long bit_representation = *(unsigned long long*)&base;
    // AND with mask to only leave exponent bits
    unsigned long long exponent_temp = bit_representation & exponent_mask;
    // bit shift the exponent all the way to the right
    exponent_temp = (exponent_temp >> exponent_bit_shift);
    // subtract a constant to get the actual value of the exponent
    exponent_temp -= exponent_value_shift;
    // add this new exponent to the previously stored exponent
    exponent += exponent_temp;
    // AND with mask to leave all the bits except for the exponent bits (in other words, set exponent bits to 0)
    bit_representation = (bit_representation & mantissa_mask);
    // OR to add exponent bits, which correspond to an exponent equal to 0
    bit_representation |= exponent_value_shifted;
    // convert the bit representation (unsigned long long) back into base (double)
    base = *(double*)&bit_representation;
}

double BigNum::ShiftAndAdd(const double value_small, const double value_large, const unsigned int shift, bool& overflow) const
{
    if(value_small == 0.0) { return value_large; }
    // convert base (double) into its bit representation (unsigned long long)
    unsigned long long bit_representation_small = *(unsigned long long*)&value_small;
    unsigned long long bit_representation_large = *(unsigned long long*)&value_large;
    // AND with mask to only leave mantissa bits
    bit_representation_small &= mantissa_mask;
    bit_representation_large &= mantissa_mask;
    // OR to add the hidden "1" to the left of the mantissa
    bit_representation_small |= hidden_mantissa_bit;
    bit_representation_large |= hidden_mantissa_bit;
    // bit shift the smaller value to make both values "equal" in terms of their exponent
    bit_representation_small = bit_representation_small >> shift;
    // add the two values in their bit representation
    unsigned long long bit_representation_new = bit_representation_large + bit_representation_small;
    // check if the resulting value is greater than 2 by checking the bit left of the hidden mantissa bit
    // overflow variable is passed outside of the function
    overflow = bit_representation_new & overflow_bit;
    // AND with mask again to get rid of the hidden "1" and the overflow bit
    bit_representation_new &= mantissa_mask;
    // bit shift the resulting value once to the right if the value was greater than 2
    if(overflow) { bit_representation_new = bit_representation_new >> 1; }
    // OR to add exponent bits, which correspond to an exponent equal to 0
    bit_representation_new |= exponent_value_shifted;
    // convert the bit representation (unsigned long long) back into base (double)
    return *(double*)&bit_representation_new;
}

std::string BigNum::StrBits() const
{
    return "base = " + \
        std::bitset<sizeof(base)*8>(*(unsigned long long*)&base).to_string() + \
        " | exponent = " + \
        std::bitset<sizeof(exponent)*8>(exponent).to_string();
}

std::string BigNum::StrBase2() const
{
    return std::to_string(base) + "*2^" + std::to_string(exponent);
}

std::string BigNum::StrBase10() const
{
    double exponent_base10 = exponent / log2_10;
    unsigned long long exponent_whole_base10 = exponent_base10;
    double exponent_reminder = exponent_base10 - exponent_whole_base10;
    double base_base10 = std::pow(10.0, exponent_reminder) * base;
    return std::to_string(base_base10) + "*10^" + std::to_string(exponent_whole_base10);
}

void   BigNum::operator= (const BigNum& other) { base = other.base; exponent = other.exponent; }
void   BigNum::operator= (const unsigned long long& other) { base = other; exponent = 0; Normalize(); }

BigNum BigNum::operator+ (const BigNum& other) const { BigNum result = BigNum(*this); result += other; return result; }
BigNum BigNum::operator* (const BigNum& other) const { BigNum result = BigNum(*this); result *= other; return result; }
BigNum BigNum::operator/ (const BigNum& other) const { BigNum result = BigNum(*this); result /= other; return result; }

void   BigNum::operator+=(const BigNum& other)
{
    // This operator is about 12 times slower than adding long double to long double
    if(exponent > other.exponent)
    {
        const unsigned long long exp_diff = exponent - other.exponent;
        bool overflow = false;
        base = ShiftAndAdd(other.base, base, exp_diff, overflow);
        if(overflow) { exponent++; }
        return;
    }
    else if(exponent < other.exponent)
    {
        const unsigned long long exp_diff = other.exponent - exponent;
        bool overflow = false;
        base = ShiftAndAdd(base, other.base, exp_diff, overflow);
        exponent = other.exponent;
        if(overflow) { exponent++; }
        return;
    }
    else  // exponent == other.exponent
    {
        base += other.base;
        Normalize();
        return;
    }
}

void   BigNum::operator*=(const BigNum& other)
{ 
    base *= other.base;
    if(base != 0.0)
    {
        exponent += other.exponent;
        Normalize();
    }
    else
    {
        exponent = 0ULL;
    }
}

void   BigNum::operator/=(const BigNum& other)
{
    if(other.base == 0.0) { throw std::runtime_error("ERROR: BigNum::operator/=(const BigNum&): Division by zero!"); }
    base /= other.base;
    if(base != 0.0)
    {
        exponent -= other.exponent;
        Normalize();
    }
}

BigNum BigNum::operator+ (const unsigned long long& other) const { BigNum result = BigNum(*this); result += other; return result; }
BigNum BigNum::operator* (const unsigned long long& other) const { BigNum result = BigNum(*this); result *= other; return result; }
BigNum BigNum::operator/ (const unsigned long long& other) const { BigNum result = BigNum(*this); result /= other; return result; }

void   BigNum::operator+=(const unsigned long long& other) { BigNum temp = BigNum(other); *this += temp; }
void   BigNum::operator*=(const unsigned long long& other) { base *= other; Normalize(); }
void   BigNum::operator/=(const unsigned long long& other)
{
    if(other == 0ULL) { throw std::runtime_error("ERROR: BigNum::operator/=(const unsigned long long&): Division by zero!"); }
    base /= other;
    Normalize();
}

bool   BigNum::operator> (const BigNum& other) const { return (exponent > other.exponent || (exponent == other.exponent && base > other.exponent)); }
bool   BigNum::operator>=(const BigNum& other) const { return (exponent > other.exponent || (exponent == other.exponent && base >= other.exponent)); }
bool   BigNum::operator< (const BigNum& other) const { return (exponent < other.exponent || (exponent == other.exponent && base < other.exponent)); }
bool   BigNum::operator<=(const BigNum& other) const { return (exponent < other.exponent || (exponent == other.exponent && base <= other.exponent)); }
bool   BigNum::operator==(const BigNum& other) const { return (base == other.base && exponent == other.exponent); }
bool   BigNum::operator!=(const BigNum& other) const { return (base != other.base || exponent != other.exponent); }
