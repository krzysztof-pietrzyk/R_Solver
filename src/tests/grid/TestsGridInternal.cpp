// ========================================================================= //
// ============================== ENVIRONMENT ============================== //
// ========================================================================= //

// UnitTest environment
#include "../UnitTestEnv.hpp"

// tested interface
#include "../../grid/GridInternal.hpp"

// prohect includes

// std includes


// ========================================================================= //
// ============================ MOCKED CLASSES ============================= //
// ========================================================================= //

class MockGridInternal : public GridInternal
{
    public:

    MockGridInternal(GridDimensions dim) : GridInternal(dim) {}

    std::vector<std::vector<uint32_t>>& GetAllNeighbors() { return neighbors; }

    MOCK_METHOD(bool, CheckVisible, (uint32_t), (const, override));
};

// ========================================================================= //
// ============================= TEST FIXTURES ============================= //
// ========================================================================= //

using CreationFixtureParams = tuple<GridDimensions, bool>;

class GridInternalCreationFixture : public TestWithParam<CreationFixtureParams>
{
    // dimensions, isExpectedThrow
};

TEST_P(GridInternalCreationFixture, Creation)
{
    CreationFixtureParams test_params = GetParam();
    const GridDimensions dim = get<0>(test_params);
    const bool isExpectedThorw = get<1>(test_params);

    if(isExpectedThorw)
    {
        ASSERT_THROW(MockGridInternal grid(dim), std::runtime_error);
    }
    else
    {
        ASSERT_NO_THROW(MockGridInternal grid(dim));
    }
}

INSTANTIATE_TEST_CASE_P(TestsGridInternal, GridInternalCreationFixture, Values(
    CreationFixtureParams(GridDimensions(1, 1, 1), true),
    CreationFixtureParams(GridDimensions(1, 1, 0), true),
    CreationFixtureParams(GridDimensions(3, 0, 1), true),
    CreationFixtureParams(GridDimensions(0, 3, 1), true),
    CreationFixtureParams(GridDimensions(3, 3, 0), true),
    CreationFixtureParams(GridDimensions(3, 3, 9), true),
    CreationFixtureParams(GridDimensions(3, 3, 10), true),
    CreationFixtureParams(GridDimensions(3, 3, 8), false),
    CreationFixtureParams(GridDimensions(9, 9, 10), false),
    CreationFixtureParams(GridDimensions(16, 16, 40), false),
    CreationFixtureParams(GridDimensions(30, 16, 99), false),
    CreationFixtureParams(GridDimensions(80, 80, 999), false),
    CreationFixtureParams(GridDimensions(1024, 3, 100), false),
    CreationFixtureParams(GridDimensions(1025, 3, 100), true),
    CreationFixtureParams(GridDimensions(3, 1024, 100), false),
    CreationFixtureParams(GridDimensions(3, 1025, 100), true)
));

// ========================================================================= //
// ============================== TEST CASES =============================== //
// ========================================================================= //

TEST(TestsGridInternal, FindNeighbors3x3)
{
    const GridDimensions dim(3, 3, 3);
    MockGridInternal grid(dim);

    ASSERT_THAT(grid.GetAllNeighbors(), ElementsAre(
        ElementsAre(1, 3, 4),
        ElementsAre(0, 2, 3, 4, 5),
        ElementsAre(1, 4, 5),
        ElementsAre(0, 1, 4, 6, 7),
        ElementsAre(0, 1, 2, 3, 5, 6, 7, 8),
        ElementsAre(1, 2, 4, 7, 8),
        ElementsAre(3, 4, 7),
        ElementsAre(3, 4, 5, 6, 8),
        ElementsAre(4, 5, 7)
    ));
}

TEST(TestsGridInternal, FindNeighbors1x3)
{
    const GridDimensions dim(1, 3, 1);
    MockGridInternal grid(dim);

    ASSERT_THAT(grid.GetAllNeighbors(), ElementsAre(
        ElementsAre(1),
        ElementsAre(0, 2),
        ElementsAre(1)
    ));
}

TEST(TestsGridInternal, FindNeighbors3x1)
{
    const GridDimensions dim(3, 1, 1);
    MockGridInternal grid(dim);

    ASSERT_THAT(grid.GetAllNeighbors(), ElementsAre(
        ElementsAre(1),
        ElementsAre(0, 2),
        ElementsAre(1)
    ));
}

TEST(TestsGridInternal, FindNeighbors2x2)
{
    const GridDimensions dim(2, 2, 1);
    MockGridInternal grid(dim);

    ASSERT_THAT(grid.GetAllNeighbors(), ElementsAre(
        ElementsAre(1, 2, 3),
        ElementsAre(0, 2, 3),
        ElementsAre(0, 1, 3),
        ElementsAre(0, 1, 2)
    ));
}

TEST(TestsGridInternal, FieldValueVisible)
{
    const GridDimensions dim(3, 3, 3);
    const uint32_t input_field = 3;

    MockGridInternal grid(dim);

    EXPECT_CALL(grid, CheckVisible(input_field)).WillOnce(Return(true));

    EXPECT_NO_THROW(grid.GetFieldValue(input_field));
}

TEST(TestsGridInternal, FieldValueInvisible)
{
    const GridDimensions dim(3, 3, 3);
    const uint32_t input_field = 3;

    MockGridInternal grid(dim);

    EXPECT_CALL(grid, CheckVisible(input_field)).WillOnce(Return(false));

    EXPECT_THROW(grid.GetFieldValue(input_field), std::runtime_error);
}

// ========================================================================= //
// =========================== TEST DATA SOURCES =========================== //
// ========================================================================= //
