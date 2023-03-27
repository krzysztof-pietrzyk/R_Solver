// ========================================================================= //
// ============================== ENVIRONMENT ============================== //
// ========================================================================= //

// UnitTest environment
#include "../UnitTestEnv.hpp"

// Other libraries

// Tested interface
#include "../../utils/CachedVector.hpp"

// ========================================================================= //
// ============================ MOCKED CLASSES ============================= //
// ========================================================================= //

class MockCachedVector : public CachedVector
{
    public:

    MockCachedVector(size_t max_size) : CachedVector(max_size) {}

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

TEST(TestCachedVector, CurrentIndex)
{
    size_t tested_size = 5U;
    MockCachedVector tested_vector = MockCachedVector(tested_size);

    EXPECT_EQ(tested_vector.CurrentIndex(), 0);
    tested_vector.Add(1);
    EXPECT_EQ(tested_vector.CurrentIndex(), 1);
    tested_vector.Add(0);
    EXPECT_EQ(tested_vector.CurrentIndex(), 2);
    tested_vector.Add(3);
    EXPECT_EQ(tested_vector.CurrentIndex(), 3);
    tested_vector.Remove(0);
    EXPECT_EQ(tested_vector.CurrentIndex(), 2);
    tested_vector.Remove(3);
    EXPECT_EQ(tested_vector.CurrentIndex(), 1);
    tested_vector.Remove(1);
    EXPECT_EQ(tested_vector.CurrentIndex(), 0);
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

    EXPECT_EQ(tested_vector.Begin(), tested_vector.GetDataVector().begin());
}

TEST(TestCachedVector, IteratorAt)
{
    size_t tested_size = 5U;
    MockCachedVector tested_vector = MockCachedVector(tested_size);

    tested_vector.Add(1);
    tested_vector.Add(0);
    tested_vector.Add(3);

    EXPECT_EQ(tested_vector.At(1), tested_vector.GetDataVector().begin() + 1);
}

TEST(TestCachedVector, IteratorEnd)
{
    size_t tested_size = 5U;
    MockCachedVector tested_vector = MockCachedVector(tested_size);

    tested_vector.Add(1);
    tested_vector.Add(0);
    tested_vector.Add(3);

    EXPECT_EQ(tested_vector.End(), tested_vector.GetDataVector().begin() + 3);
}

// ========================================================================= //
// =========================== TEST DATA SOURCES =========================== //
// ========================================================================= //
