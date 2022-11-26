// ========================================================================= //
// ============================== ENVIRONMENT ============================== //
// ========================================================================= //

// UnitTest environment
#include "../UnitTestEnv.hpp"

// Other libraries

#include <math.h>

// Tested interface
#include "../../utils/BigNum.hpp"

// ========================================================================= //
// ============================ MOCKED CLASSES ============================= //
// ========================================================================= //

class MockBigNum : public BigNum
{
    public:

    MockBigNum() : BigNum() {}
    MockBigNum(int64_t a) : BigNum(a) {}
    MockBigNum(BigNum a) : BigNum(a) {}

    double GetBase() const { return base; }
    int64_t GetExponent() const { return exponent; }
};

// ========================================================================= //
// ============================= TEST FIXTURES ============================= //
// ========================================================================= //

using OperatorAssignULLFixtureParams = tuple<uint64_t, double, uint64_t>;

class BigNumOperatorAssignULLFixture : public TestWithParam<OperatorAssignULLFixtureParams>
{
    // test_value, expected_base, expected_exponent
};

TEST_P(BigNumOperatorAssignULLFixture, OperatorAssignULL)
{
    const OperatorAssignULLFixtureParams params = GetParam();
    const uint64_t test_value = get<0>(params);
    const double expected_base = get<1>(params);
    const uint64_t expected_exponent = get<2>(params);

    MockBigNum num;
    num = test_value;

    EXPECT_EQ(num.GetBase(), expected_base);
    EXPECT_EQ(num.GetExponent(), expected_exponent);
}

INSTANTIATE_TEST_CASE_P(TestBigNum, BigNumOperatorAssignULLFixture, Values(
    OperatorAssignULLFixtureParams(0, 0.0, 0),
    OperatorAssignULLFixtureParams(1, 1.0, 0),
    OperatorAssignULLFixtureParams(2, 1.0, 1),
    OperatorAssignULLFixtureParams(1056, 1.03125, 10),
    OperatorAssignULLFixtureParams(1025, 1.0009765625, 10),
    OperatorAssignULLFixtureParams(1835008ULL, 1.75, 20),
    OperatorAssignULLFixtureParams(4294967296ULL, 1.0, 32),
    OperatorAssignULLFixtureParams(9223372036854775808ULL, 1.0, 63)
));

// ========================================================================= //
// ========================================================================= //
// ========================================================================= //

using OperatorPlusFixtureParams = tuple<BigNum, BigNum, MockBigNum>;

class BigNumOperatorPlusFixture : public TestWithParam<OperatorPlusFixtureParams>
{
    // value_a, value_b, expected_value
};

TEST_P(BigNumOperatorPlusFixture, OperatorPlus)
{
    const OperatorPlusFixtureParams params = GetParam();
    const BigNum value_a = get<0>(params);
    const BigNum value_b = get<1>(params);
    const MockBigNum expected_value = get<2>(params);

    MockBigNum num = value_a + value_b;

    EXPECT_EQ(num.GetBase(), expected_value.GetBase());
    EXPECT_EQ(num.GetExponent(), expected_value.GetExponent());
}

INSTANTIATE_TEST_CASE_P(TestBigNum, BigNumOperatorPlusFixture, Values(
    OperatorPlusFixtureParams(0, 0, 0),
    OperatorPlusFixtureParams(1, 0, 1),
    OperatorPlusFixtureParams(10, 0, 10),
    OperatorPlusFixtureParams(0, 1, 1),
    OperatorPlusFixtureParams(0, 10, 10),
    OperatorPlusFixtureParams(1, 1, 2),
    OperatorPlusFixtureParams(10, 10, 20),
    OperatorPlusFixtureParams(4294967296ULL, 4294967296ULL, 8589934592ULL)
));

// ========================================================================= //
// ========================================================================= //
// ========================================================================= //

using OperatorMultiplyFixtureParams = tuple<BigNum, BigNum, MockBigNum>;

class BigNumOperatorMultiplyFixture : public TestWithParam<OperatorMultiplyFixtureParams>
{
    // value_a, value_b, expected_value
};

TEST_P(BigNumOperatorMultiplyFixture, OperatorMultiply)
{
    const OperatorMultiplyFixtureParams params = GetParam();
    const BigNum value_a = get<0>(params);
    const BigNum value_b = get<1>(params);
    const MockBigNum expected_value = get<2>(params);

    MockBigNum num = value_a * value_b;

    EXPECT_EQ(num.GetBase(), expected_value.GetBase());
    EXPECT_EQ(num.GetExponent(), expected_value.GetExponent());
}

INSTANTIATE_TEST_CASE_P(TestBigNum, BigNumOperatorMultiplyFixture, Values(
    OperatorMultiplyFixtureParams(0, 0, 0),
    OperatorMultiplyFixtureParams(1, 0, 0),
    OperatorMultiplyFixtureParams(10, 0, 0),
    OperatorMultiplyFixtureParams(0, 1, 0),
    OperatorMultiplyFixtureParams(0, 10, 0),
    OperatorMultiplyFixtureParams(1, 1, 1),
    OperatorMultiplyFixtureParams(10, 10, 100),
    OperatorMultiplyFixtureParams(1307674368000ULL, 16ULL, 20922789888000ULL)
));

// ========================================================================= //
// ========================================================================= //
// ========================================================================= //

using OperatorDivideFixtureParams = tuple<BigNum, BigNum, MockBigNum>;

class BigNumOperatorDivideFixture : public TestWithParam<OperatorDivideFixtureParams>
{
    // value_a, value_b, expected_value
};

TEST_P(BigNumOperatorDivideFixture, OperatorDivive)
{
    const OperatorDivideFixtureParams params = GetParam();
    const BigNum value_a = get<0>(params);
    const BigNum value_b = get<1>(params);
    const MockBigNum expected_value = get<2>(params);

    MockBigNum num = value_a / value_b;

    EXPECT_EQ(num.GetBase(), expected_value.GetBase());
    EXPECT_EQ(num.GetExponent(), expected_value.GetExponent());
}

INSTANTIATE_TEST_CASE_P(TestBigNum, BigNumOperatorDivideFixture, Values(
    OperatorDivideFixtureParams(0, 1, 0),
    OperatorDivideFixtureParams(0, 10, 0),
    OperatorDivideFixtureParams(1, 1, 1),
    OperatorDivideFixtureParams(10, 10, 1),
    OperatorDivideFixtureParams(20922789888000ULL, 16ULL, 1307674368000ULL)
));

// ========================================================================= //
// ========================================================================= //
// ========================================================================= //

using OperatorPlusULLFixtureParams = tuple<BigNum, uint64_t, MockBigNum>;

class BigNumOperatorPlusULLFixture : public TestWithParam<OperatorPlusULLFixtureParams>
{
    // value_a, value_b, expected_value
};

TEST_P(BigNumOperatorPlusULLFixture, OperatorPlusULL)
{
    const OperatorPlusULLFixtureParams params = GetParam();
    const BigNum value_a = get<0>(params);
    const uint64_t value_b = get<1>(params);
    const MockBigNum expected_value = get<2>(params);

    MockBigNum num = value_a + value_b;

    EXPECT_EQ(num.GetBase(), expected_value.GetBase());
    EXPECT_EQ(num.GetExponent(), expected_value.GetExponent());
}

INSTANTIATE_TEST_CASE_P(TestBigNum, BigNumOperatorPlusULLFixture, Values(
    OperatorPlusULLFixtureParams(0, 0, 0),
    OperatorPlusULLFixtureParams(1, 0, 1),
    OperatorPlusULLFixtureParams(10, 0, 10),
    OperatorPlusULLFixtureParams(0, 1, 1),
    OperatorPlusULLFixtureParams(0, 10, 10),
    OperatorPlusULLFixtureParams(1, 1, 2),
    OperatorPlusULLFixtureParams(10, 10, 20),
    OperatorPlusULLFixtureParams(4294967296ULL, 4294967296ULL, 8589934592ULL)
));

// ========================================================================= //
// ========================================================================= //
// ========================================================================= //

using OperatorMultiplyULLFixtureParams = tuple<BigNum, BigNum, MockBigNum>;

class BigNumOperatorMultiplyULLFixture : public TestWithParam<OperatorMultiplyULLFixtureParams>
{
    // value_a, value_b, expected_value
};

TEST_P(BigNumOperatorMultiplyULLFixture, OperatorMultiplyULL)
{
    const OperatorMultiplyULLFixtureParams params = GetParam();
    const BigNum value_a = get<0>(params);
    const BigNum value_b = get<1>(params);
    const MockBigNum expected_value = get<2>(params);

    MockBigNum num = value_a * value_b;

    EXPECT_EQ(num.GetBase(), expected_value.GetBase());
    EXPECT_EQ(num.GetExponent(), expected_value.GetExponent());
}

INSTANTIATE_TEST_CASE_P(TestBigNum, BigNumOperatorMultiplyULLFixture, Values(
    OperatorMultiplyULLFixtureParams(0, 0, 0),
    OperatorMultiplyULLFixtureParams(1, 0, 0),
    OperatorMultiplyULLFixtureParams(10, 0, 0),
    OperatorMultiplyULLFixtureParams(0, 1, 0),
    OperatorMultiplyULLFixtureParams(0, 10, 0),
    OperatorMultiplyULLFixtureParams(1, 1, 1),
    OperatorMultiplyULLFixtureParams(10, 10, 100),
    OperatorMultiplyULLFixtureParams(1307674368000ULL, 16ULL, 20922789888000ULL)
));

// ========================================================================= //
// ========================================================================= //
// ========================================================================= //

using OperatorDivideULLFixtureParams = tuple<BigNum, BigNum, MockBigNum>;

class BigNumOperatorDivideULLFixture : public TestWithParam<OperatorDivideULLFixtureParams>
{
    // value_a, value_b, expected_value
};

TEST_P(BigNumOperatorDivideULLFixture, OperatorDiviveULL)
{
    const OperatorDivideULLFixtureParams params = GetParam();
    const BigNum value_a = get<0>(params);
    const BigNum value_b = get<1>(params);
    const MockBigNum expected_value = get<2>(params);

    MockBigNum num = value_a / value_b;

    EXPECT_EQ(num.GetBase(), expected_value.GetBase());
    EXPECT_EQ(num.GetExponent(), expected_value.GetExponent());
}

INSTANTIATE_TEST_CASE_P(TestBigNum, BigNumOperatorDivideULLFixture, Values(
    OperatorDivideULLFixtureParams(0, 1, 0),
    OperatorDivideULLFixtureParams(0, 10, 0),
    OperatorDivideULLFixtureParams(1, 1, 1),
    OperatorDivideULLFixtureParams(10, 10, 1),
    OperatorDivideULLFixtureParams(20922789888000ULL, 16ULL, 1307674368000ULL)
));

// ========================================================================= //
// ============================== TEST CASES =============================== //
// ========================================================================= //

TEST(TestBigNum, OperatorAssign)
{
    const uint64_t test_value = 1234567890ULL;
    const MockBigNum first(test_value);
    const MockBigNum second = first;

    EXPECT_EQ(first.GetBase(), second.GetBase());
    EXPECT_EQ(first.GetExponent(), second.GetExponent());
}

TEST(TestBigNum, DivideByZeroULL)
{
    const uint64_t test_value = 1234567890ULL;
    const uint64_t zero = 0;
    const MockBigNum num(test_value);
    MockBigNum second;
    
    EXPECT_THROW(second = num / zero, std::runtime_error);
}

TEST(TestBigNum, DivideByZero)
{
    const uint64_t test_value = 1234567890ULL;
    const uint64_t zero = 0;
    const MockBigNum num(test_value);
    const MockBigNum num_zero(zero);
    MockBigNum second;
    
    EXPECT_THROW(second = num / num_zero, std::runtime_error);
}

TEST(TestBigNum, FactorialAndReciprocal)
{
    const uint32_t factorial_max = 1000;
    const long double allowed_error = 1E-9L;
    MockBigNum factorial_num = 1;
    MockBigNum reciprocal_num = 1;
    long double factorial_double = 1.0;
    long double reciprocal_double = 1.0;

    for(uint32_t i = 1; i <= factorial_max; i++)
    {
        factorial_num *= i; 
        reciprocal_num /= i;
        factorial_double *= i;
        reciprocal_double /= i;
    }

    const long double final_factorial_value = (long double)factorial_num.GetBase() * pow(2.0L, factorial_num.GetExponent());
    const long double final_reciprocal_value = (long double)reciprocal_num.GetBase() * pow(2.0L, reciprocal_num.GetExponent());
    const long double factorial_error = abs(final_factorial_value - factorial_double);
    const long double reciprocal_error = abs(final_reciprocal_value - reciprocal_double);
    const long double allowed_factorial_error = factorial_double * allowed_error;
    const long double allowed_reciprocal_error = reciprocal_double * allowed_error;

    EXPECT_LT(factorial_error, allowed_factorial_error);
    EXPECT_LT(reciprocal_error, allowed_reciprocal_error);
}



// ========================================================================= //
// =========================== TEST DATA SOURCES =========================== //
// ========================================================================= //
