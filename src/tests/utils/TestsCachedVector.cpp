// ========================================================================= //
// ============================== ENVIRONMENT ============================== //
// ========================================================================= //

// UnitTest environment
#include "../UnitTestEnv.hpp"

// tested interface
#include "../../utils/CachedVector.hpp"

// project includes

// std includes


// ========================================================================= //
// ============================ MOCKED CLASSES ============================= //
// ========================================================================= //

class MockCachedVector : public CachedVector
{
    public:

    MockCachedVector(size_t max_size) : CachedVector(max_size) {}
    MockCachedVector(const std::vector<bool>& _is_present) : CachedVector(_is_present) {}
    MockCachedVector(const std::vector<uint32_t>& _data, size_t _max_size) : CachedVector(_data, _max_size) {}

    std::vector<uint32_t>& GetDataVector() { return data; }
    std::vector<bool>& GetIsPresentVector() { return is_present; }
    size_t& GetDataIndex() { return data_index; }
};

// ========================================================================= //
// ============================= TEST FIXTURES ============================= //
// ========================================================================= //



// ========================================================================= //
// ========================================================================= //
// ========================================================================= //



// ========================================================================= //
// ============================== TEST CASES =============================== //
// ========================================================================= //

TEST(TestCachedVector, InitializeEmptyVectorSize0)
{
    size_t tested_size = 0U;
    MockCachedVector tested_vector = MockCachedVector(tested_size);
    EXPECT_EQ(tested_vector.GetDataIndex(), 0U);
    EXPECT_EQ(tested_vector.GetDataVector(), std::vector<uint32_t>());
    EXPECT_EQ(tested_vector.GetIsPresentVector(), std::vector<bool>());
}

TEST(TestCachedVector, InitializeEmptyVectorSize1)
{
    size_t tested_size = 1U;
    MockCachedVector tested_vector = MockCachedVector(tested_size);
    EXPECT_EQ(tested_vector.GetDataIndex(), 0U);
    EXPECT_EQ(tested_vector.GetDataVector(), std::vector<uint32_t>({0}));
    EXPECT_EQ(tested_vector.GetIsPresentVector(), std::vector<bool>({false}));
}

TEST(TestCachedVector, InitializeEmptyVectorSize5)
{
    size_t tested_size = 5U;
    MockCachedVector tested_vector = MockCachedVector(tested_size);
    EXPECT_EQ(tested_vector.GetDataIndex(), 0U);
    EXPECT_EQ(tested_vector.GetDataVector(), std::vector<uint32_t>({0, 0, 0, 0, 0}));
    EXPECT_EQ(tested_vector.GetIsPresentVector(), std::vector<bool>({false, false, false, false, false}));
}

TEST(TestCachedVector, InitializeVectorWithDataVector)
{
    size_t tested_size = 6U;
    std::vector<uint32_t> data_vector = {5, 1, 3};
    MockCachedVector tested_vector = MockCachedVector(data_vector, tested_size);
    EXPECT_EQ(tested_vector.GetDataIndex(), 3U);
    EXPECT_EQ(tested_vector.GetDataVector(), std::vector<uint32_t>({5, 1, 3, 0, 0, 0}));
    EXPECT_EQ(tested_vector.GetIsPresentVector(), std::vector<bool>({false, true, false, true, false, true}));
}

TEST(TestCachedVector, InitializeVectorWithIsPresentVector)
{
    std::vector<bool> is_present_vector = {false, true, false, true, false, true};
    MockCachedVector tested_vector = MockCachedVector(is_present_vector);
    EXPECT_EQ(tested_vector.GetDataIndex(), 3U);
    EXPECT_EQ(tested_vector.MaxSize(), 6U);
    EXPECT_EQ(tested_vector.GetDataVector(), std::vector<uint32_t>({1, 3, 5, 0, 0, 0}));
    EXPECT_EQ(tested_vector.GetIsPresentVector(), std::vector<bool>({false, true, false, true, false, true}));
}

TEST(TestCachedVector, AddOneValue)
{
    size_t tested_size = 5U;
    MockCachedVector tested_vector = MockCachedVector(tested_size);

    tested_vector.Add(1);

    EXPECT_EQ(tested_vector.GetDataIndex(), 1U);
    EXPECT_EQ(tested_vector.GetDataVector(), std::vector<uint32_t>({1, 0, 0, 0, 0}));
    EXPECT_EQ(tested_vector.GetIsPresentVector(), std::vector<bool>({false, true, false, false, false}));
}

TEST(TestCachedVector, AddMultipleValues)
{
    size_t tested_size = 5U;
    MockCachedVector tested_vector = MockCachedVector(tested_size);

    tested_vector.Add(1);
    tested_vector.Add(0);
    tested_vector.Add(3);

    EXPECT_EQ(tested_vector.GetDataIndex(), 3U);
    EXPECT_EQ(tested_vector.GetDataVector(), std::vector<uint32_t>({1, 0, 3, 0, 0}));
    EXPECT_EQ(tested_vector.GetIsPresentVector(), std::vector<bool>({true, true, false, true, false}));
}

TEST(TestCachedVector, RemoveOneValue)
{
    size_t tested_size = 5U;
    MockCachedVector tested_vector = MockCachedVector(tested_size);

    tested_vector.Add(1);
    tested_vector.Add(0);
    tested_vector.Add(3);
    tested_vector.Remove(0);

    EXPECT_EQ(tested_vector.GetDataIndex(), 2U);
    EXPECT_EQ(tested_vector.GetDataVector(), std::vector<uint32_t>({1, 3, 3, 0, 0}));
    EXPECT_EQ(tested_vector.GetIsPresentVector(), std::vector<bool>({false, true, false, true, false}));
}

TEST(TestCachedVector, RemoveMultipleValues)
{
    size_t tested_size = 5U;
    MockCachedVector tested_vector = MockCachedVector(tested_size);

    tested_vector.Add(1);
    tested_vector.Add(0);
    tested_vector.Add(3);
    tested_vector.Remove(0);
    tested_vector.Remove(3);

    EXPECT_EQ(tested_vector.GetDataIndex(), 1U);
    EXPECT_EQ(tested_vector.GetDataVector(), std::vector<uint32_t>({1, 3, 3, 0, 0}));
    EXPECT_EQ(tested_vector.GetIsPresentVector(), std::vector<bool>({false, true, false, false, false}));
}

TEST(TestCachedVector, RemoveAllValues)
{
    size_t tested_size = 5U;
    MockCachedVector tested_vector = MockCachedVector(tested_size);

    tested_vector.Add(1);
    tested_vector.Add(0);
    tested_vector.Add(3);
    tested_vector.Remove(0);
    tested_vector.Remove(3);
    tested_vector.Remove(1);

    EXPECT_EQ(tested_vector.GetDataIndex(), 0U);
    EXPECT_EQ(tested_vector.GetDataVector(), std::vector<uint32_t>({1, 3, 3, 0, 0}));
    EXPECT_EQ(tested_vector.GetIsPresentVector(), std::vector<bool>({false, false, false, false, false}));
}

TEST(TestCachedVector, AddRemove)
{
    size_t tested_size = 5U;
    MockCachedVector tested_vector = MockCachedVector(tested_size);

    tested_vector.Add(1);
    tested_vector.Remove(1);
    tested_vector.Add(0);
    tested_vector.Remove(0);
    tested_vector.Add(3);
    tested_vector.Remove(3);
    
    EXPECT_EQ(tested_vector.GetDataIndex(), 0U);
    EXPECT_EQ(tested_vector.GetDataVector(), std::vector<uint32_t>({3, 0, 0, 0, 0}));
    EXPECT_EQ(tested_vector.GetIsPresentVector(), std::vector<bool>({false, false, false, false, false}));
}

TEST(TestCachedVector, ContainsValues)
{
    size_t tested_size = 5U;
    MockCachedVector tested_vector = MockCachedVector(tested_size);

    tested_vector.Add(1);
    tested_vector.Add(0);
    tested_vector.Add(3);
    EXPECT_TRUE(tested_vector.Contains(0));
    EXPECT_TRUE(tested_vector.Contains(1));
    EXPECT_FALSE(tested_vector.Contains(2));
    EXPECT_TRUE(tested_vector.Contains(3));
    tested_vector.Remove(0);
    tested_vector.Remove(3);
    tested_vector.Remove(1);
    EXPECT_FALSE(tested_vector.Contains(0));
    EXPECT_FALSE(tested_vector.Contains(1));
    EXPECT_FALSE(tested_vector.Contains(2));
    EXPECT_FALSE(tested_vector.Contains(3));
}

TEST(TestCachedVector, Index)
{
    size_t tested_size = 5U;
    MockCachedVector tested_vector = MockCachedVector(tested_size);

    EXPECT_EQ(tested_vector.Index(), 0);
    tested_vector.Add(1);
    EXPECT_EQ(tested_vector.Index(), 1);
    tested_vector.Add(0);
    EXPECT_EQ(tested_vector.Index(), 2);
    tested_vector.Add(3);
    EXPECT_EQ(tested_vector.Index(), 3);
    tested_vector.Remove(0);
    EXPECT_EQ(tested_vector.Index(), 2);
    tested_vector.Remove(3);
    EXPECT_EQ(tested_vector.Index(), 1);
    tested_vector.Remove(1);
    EXPECT_EQ(tested_vector.Index(), 0);
}

TEST(TestCachedVector, Clear)
{
    size_t tested_size = 5U;
    MockCachedVector tested_vector = MockCachedVector(tested_size);

    tested_vector.Add(1);
    tested_vector.Add(0);
    tested_vector.Add(3);
    tested_vector.Clear();

    EXPECT_EQ(tested_vector.GetDataIndex(), 0U);
    EXPECT_EQ(tested_vector.GetDataVector(), std::vector<uint32_t>({1, 0, 3, 0, 0}));
    EXPECT_EQ(tested_vector.GetIsPresentVector(), std::vector<bool>({false, false, false, false, false}));
}

TEST(TestCachedVector, IteratorBegin)
{
    size_t tested_size = 5U;
    MockCachedVector tested_vector = MockCachedVector(tested_size);

    tested_vector.Add(1);
    tested_vector.Add(0);
    tested_vector.Add(3);

    EXPECT_EQ(tested_vector.begin(), tested_vector.GetDataVector().begin());
}

TEST(TestCachedVector, IteratorAt)
{
    size_t tested_size = 5U;
    MockCachedVector tested_vector = MockCachedVector(tested_size);

    tested_vector.Add(1);
    tested_vector.Add(0);
    tested_vector.Add(3);

    EXPECT_EQ(tested_vector.at(1), tested_vector.GetDataVector().begin() + 1);
}

TEST(TestCachedVector, IteratorEnd)
{
    size_t tested_size = 5U;
    MockCachedVector tested_vector = MockCachedVector(tested_size);

    tested_vector.Add(1);
    tested_vector.Add(0);
    tested_vector.Add(3);

    EXPECT_EQ(tested_vector.end(), tested_vector.GetDataVector().begin() + 3);
}

TEST(TestCachedVector, OperatorAssign)
{
    size_t tested_size = 5U;
    MockCachedVector tested_vector_a = MockCachedVector(tested_size);
    MockCachedVector tested_vector_b = MockCachedVector(tested_size);

    tested_vector_a.Add(1);
    tested_vector_a.Add(0);
    tested_vector_a.Add(3);

    CachedVector::CopyFromTo(tested_vector_a, tested_vector_b);

    EXPECT_EQ(tested_vector_a.GetDataVector(), tested_vector_b.GetDataVector());
    EXPECT_EQ(tested_vector_a.GetIsPresentVector(), tested_vector_b.GetIsPresentVector());
    EXPECT_EQ(tested_vector_a.GetDataIndex(), tested_vector_b.GetDataIndex());
    EXPECT_NE(&tested_vector_a, &tested_vector_b);
}

TEST(TestCachedVector, OperatorAssignNotEmpty)
{
    size_t tested_size = 5U;
    MockCachedVector tested_vector_a = MockCachedVector(tested_size);
    MockCachedVector tested_vector_b = MockCachedVector(tested_size);

    tested_vector_a.Add(1);
    tested_vector_a.Add(0);
    tested_vector_a.Add(3);

    tested_vector_b.Add(4);
    tested_vector_b.Add(3);
    tested_vector_b.Add(2);

    CachedVector::CopyFromTo(tested_vector_a, tested_vector_b);

    EXPECT_EQ(tested_vector_a.GetDataVector(), tested_vector_b.GetDataVector());
    EXPECT_EQ(tested_vector_a.GetIsPresentVector(), tested_vector_b.GetIsPresentVector());
    EXPECT_EQ(tested_vector_a.GetDataIndex(), tested_vector_b.GetDataIndex());
    EXPECT_NE(&tested_vector_a, &tested_vector_b);
}

TEST(TestCachedVector, OperatorEquals)
{
    size_t tested_size = 5U;
    MockCachedVector tested_vector_a = MockCachedVector(tested_size);
    MockCachedVector tested_vector_b = MockCachedVector(tested_size);

    EXPECT_TRUE(tested_vector_a == tested_vector_b);
    tested_vector_a.Add(1);
    EXPECT_FALSE(tested_vector_a == tested_vector_b);
    tested_vector_a.Add(0);
    EXPECT_FALSE(tested_vector_a == tested_vector_b);
    tested_vector_a.Add(3);
    EXPECT_FALSE(tested_vector_a == tested_vector_b);

    tested_vector_b.Add(1);
    EXPECT_FALSE(tested_vector_a == tested_vector_b);
    tested_vector_b.Add(0);
    EXPECT_FALSE(tested_vector_a == tested_vector_b);
    tested_vector_b.Add(3);
    EXPECT_TRUE(tested_vector_a == tested_vector_b);
}

TEST(TestCachedVector, OperatorEqualsDifferentSize)
{
    size_t tested_size_a = 5U;
    size_t tested_size_b = 6U;
    MockCachedVector tested_vector_a = MockCachedVector(tested_size_a);
    MockCachedVector tested_vector_b = MockCachedVector(tested_size_b);

    EXPECT_FALSE(tested_vector_a == tested_vector_b);
    tested_vector_a.Add(1);
    EXPECT_FALSE(tested_vector_a == tested_vector_b);
    tested_vector_a.Add(0);
    EXPECT_FALSE(tested_vector_a == tested_vector_b);
    tested_vector_a.Add(3);
    EXPECT_FALSE(tested_vector_a == tested_vector_b);

    tested_vector_b.Add(1);
    EXPECT_FALSE(tested_vector_a == tested_vector_b);
    tested_vector_b.Add(0);
    EXPECT_FALSE(tested_vector_a == tested_vector_b);
    tested_vector_b.Add(3);
    EXPECT_FALSE(tested_vector_a == tested_vector_b);
}

// ========================================================================= //
// =========================== TEST DATA SOURCES =========================== //
// ========================================================================= //
